// Copyright 2021 Predibase. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// =============================================================================

#include "adasum_gloo.h"

namespace horovod {
namespace common {
AdasumGloo::AdasumGloo(GlooContext* gloo_context, HorovodGlobalState* global_state)
    : Adasum(global_state), gloo_context_(gloo_context) {}

AdasumGloo::~AdasumGloo() {
  if (reduction_comms_ != nullptr) {
    delete reduction_comms_;
  }
}

void AdasumGloo::InitializeVHDDReductionComms() {
  int rank = gloo_context_.ctx->rank;
  int size = gloo_context_.ctx->size;

  // Initialize communication groups for the vector halving, distance doubling
  // (VHDD) Adasum reduction. These are used in computing dot products and
  // norms for tensors whose elements are split across multiple ranks, which
  // is required for implementing the Adasum operation. The first group
  // includes two elements: this rank and it's first VHDD neighbor. The
  // subsequent groups grow to include any ranks the previous group
  // communicates with. Thus the sizes of the groups are 2,4,8... up to the
  // size of MPI_COMM_WORLD. In essence, a reduction group includes all nodes
  // that a tensor may be split across.
  MPI_Group world_group;
  MPI_Comm_group(MPI_COMM_WORLD, &world_group);
  int nearest_power_2 = 1;
  int log_size;
  for (nearest_power_2 = 1, log_size = 0; (nearest_power_2 << 1) <= size;
        nearest_power_2 = (nearest_power_2 << 1), log_size++)
    ;
  int shift_val;
  int level;
  reduction_comms_ = new MPI_Comm[log_size];
  int* node_rank = new int[size];
  for (level = 1, shift_val = 1; level < nearest_power_2;
        level = (level << 1), shift_val++) {
    int base_rank = ((rank >> shift_val) << shift_val);
    for (int i = 0; i < (level << 1); i++) {
      node_rank[i] = (base_rank + i);
    }
    MPI_Group red_group;
    MPI_Group_incl(world_group, (level << 1), node_rank, &red_group);
    MPI_Comm_create_group(MPI_COMM_WORLD, red_group, 0,
                          &reduction_comms_[shift_val - 1]);
    MPI_Group_free(&red_group);
  }
  delete[] node_rank;
  reduction_comms_initialized = true;
}

int AdasumGloo::GetLocalRankWithComm(gloo::Context local_comm) {
  return local_comm.rank();
}

int AdasumGloo::GetSizeWithComm(gloo::Context comm) {
  return comm.rank();
}

void AdasumGloo::SumAllreduceWithComm(std::vector<TensorTableEntry>& entries,
                                      void* data, int num_elements,
                                      DataType horovod_datatype, gloo::Context comm,
                                      HorovodGlobalState* global_state) {
  auto& timeline = global_state->timeline;
  timeline.ActivityStartAll(entries, GLOO_ALLREDUCE);
  std::unique_ptr<IGlooAlgorithms> gloo_algos(
      GetAlgorithmsForType(horovod_datatype, &gloo_context_));
  gloo_algos->Allreduce(data, num_elements);
  timeline.ActivityEndAll(entries);
}

void AdasumGloo::PointToPointSendRecv(
    void* input_data_buffer, int64_t input_buffer_length,
    void* output_data_buffer, int64_t output_buffer_length,
    DataType horovod_datatype, int dst_src_rank, int tag, gloo::Context communicator,
    HorovodGlobalState* global_state) {
  int status;
  int element_size =
      global_state->global_controller->GetTypeSize(horovod_datatype);
  int input_count = input_buffer_length / element_size;
  int output_count = output_buffer_length / element_size;
  int chunk_count =
      std::max((int)(global_state->adasum_mpi_chunk_size / element_size), 1);

  for (int i = 0; i < std::max(input_count, output_count); i += chunk_count) {
    status = MPI_Sendrecv((char*)input_data_buffer + i * element_size,
                          std::min(chunk_count, std::max(0, input_count - i)),
                          mpi_context_->GetMPIDataType(horovod_datatype),
                          dst_src_rank, tag,
                          (char*)output_data_buffer + i * element_size,
                          std::min(chunk_count, std::max(0, output_count - i)),
                          mpi_context_->GetMPIDataType(horovod_datatype),
                          dst_src_rank, tag, communicator, MPI_STATUS_IGNORE);
    if (status != MPI_SUCCESS) {
      throw std::logic_error(
          "MPI_SendRecv failed, see MPI output for details.");
    }
  }
}
} // namespace common
} // namespace horovod
