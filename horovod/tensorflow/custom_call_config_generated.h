// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_CUSTOMCALLCONFIG_HOROVOD_XLA_WIRE_H_
#define FLATBUFFERS_GENERATED_CUSTOMCALLCONFIG_HOROVOD_XLA_WIRE_H_

#include "flatbuffers/flatbuffers.h"

#include "../common/wire/message_generated.h"

namespace horovod {
namespace xla {
namespace wire {

struct TensorShape;

struct CustomCallConfig;

struct TensorShape FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_DIMS = 4
  };
  const flatbuffers::Vector<int64_t> *dims() const {
    return GetPointer<const flatbuffers::Vector<int64_t> *>(VT_DIMS);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_DIMS) &&
           verifier.VerifyVector(dims()) &&
           verifier.EndTable();
  }
};

struct TensorShapeBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_dims(flatbuffers::Offset<flatbuffers::Vector<int64_t>> dims) {
    fbb_.AddOffset(TensorShape::VT_DIMS, dims);
  }
  explicit TensorShapeBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  TensorShapeBuilder &operator=(const TensorShapeBuilder &);
  flatbuffers::Offset<TensorShape> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<TensorShape>(end);
    return o;
  }
};

inline flatbuffers::Offset<TensorShape> CreateTensorShape(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::Vector<int64_t>> dims = 0) {
  TensorShapeBuilder builder_(_fbb);
  builder_.add_dims(dims);
  return builder_.Finish();
}

inline flatbuffers::Offset<TensorShape> CreateTensorShapeDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const std::vector<int64_t> *dims = nullptr) {
  auto dims__ = dims ? _fbb.CreateVector<int64_t>(*dims) : 0;
  return horovod::xla::wire::CreateTensorShape(
      _fbb,
      dims__);
}

struct CustomCallConfig FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_TENSOR_NAME = 4,
    VT_TENSOR_TYPE = 6,
    VT_INPUT_SHAPES = 8,
    VT_OUTPUT_SHAPES = 10,
    VT_PRESCALE_FACTOR = 12,
    VT_POSTSCALE_FACTOR = 14,
    VT_ROOT_RANK = 16,
    VT_REDUCE_OP = 18,
    VT_PROCESS_SET_ID = 20
  };
  const flatbuffers::String *tensor_name() const {
    return GetPointer<const flatbuffers::String *>(VT_TENSOR_NAME);
  }
  horovod::common::wire::DataType tensor_type() const {
    return static_cast<horovod::common::wire::DataType>(GetField<int8_t>(VT_TENSOR_TYPE, 0));
  }
  const flatbuffers::Vector<flatbuffers::Offset<TensorShape>> *input_shapes() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<TensorShape>> *>(VT_INPUT_SHAPES);
  }
  const flatbuffers::Vector<flatbuffers::Offset<TensorShape>> *output_shapes() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<TensorShape>> *>(VT_OUTPUT_SHAPES);
  }
  float prescale_factor() const {
    return GetField<float>(VT_PRESCALE_FACTOR, 0.0f);
  }
  float postscale_factor() const {
    return GetField<float>(VT_POSTSCALE_FACTOR, 0.0f);
  }
  int32_t root_rank() const {
    return GetField<int32_t>(VT_ROOT_RANK, 0);
  }
  int32_t reduce_op() const {
    return GetField<int32_t>(VT_REDUCE_OP, 0);
  }
  int32_t process_set_id() const {
    return GetField<int32_t>(VT_PROCESS_SET_ID, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_TENSOR_NAME) &&
           verifier.VerifyString(tensor_name()) &&
           VerifyField<int8_t>(verifier, VT_TENSOR_TYPE) &&
           VerifyOffset(verifier, VT_INPUT_SHAPES) &&
           verifier.VerifyVector(input_shapes()) &&
           verifier.VerifyVectorOfTables(input_shapes()) &&
           VerifyOffset(verifier, VT_OUTPUT_SHAPES) &&
           verifier.VerifyVector(output_shapes()) &&
           verifier.VerifyVectorOfTables(output_shapes()) &&
           VerifyField<float>(verifier, VT_PRESCALE_FACTOR) &&
           VerifyField<float>(verifier, VT_POSTSCALE_FACTOR) &&
           VerifyField<int32_t>(verifier, VT_ROOT_RANK) &&
           VerifyField<int32_t>(verifier, VT_REDUCE_OP) &&
           VerifyField<int32_t>(verifier, VT_PROCESS_SET_ID) &&
           verifier.EndTable();
  }
};

struct CustomCallConfigBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_tensor_name(flatbuffers::Offset<flatbuffers::String> tensor_name) {
    fbb_.AddOffset(CustomCallConfig::VT_TENSOR_NAME, tensor_name);
  }
  void add_tensor_type(horovod::common::wire::DataType tensor_type) {
    fbb_.AddElement<int8_t>(CustomCallConfig::VT_TENSOR_TYPE, static_cast<int8_t>(tensor_type), 0);
  }
  void add_input_shapes(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<TensorShape>>> input_shapes) {
    fbb_.AddOffset(CustomCallConfig::VT_INPUT_SHAPES, input_shapes);
  }
  void add_output_shapes(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<TensorShape>>> output_shapes) {
    fbb_.AddOffset(CustomCallConfig::VT_OUTPUT_SHAPES, output_shapes);
  }
  void add_prescale_factor(float prescale_factor) {
    fbb_.AddElement<float>(CustomCallConfig::VT_PRESCALE_FACTOR, prescale_factor, 0.0f);
  }
  void add_postscale_factor(float postscale_factor) {
    fbb_.AddElement<float>(CustomCallConfig::VT_POSTSCALE_FACTOR, postscale_factor, 0.0f);
  }
  void add_root_rank(int32_t root_rank) {
    fbb_.AddElement<int32_t>(CustomCallConfig::VT_ROOT_RANK, root_rank, 0);
  }
  void add_reduce_op(int32_t reduce_op) {
    fbb_.AddElement<int32_t>(CustomCallConfig::VT_REDUCE_OP, reduce_op, 0);
  }
  void add_process_set_id(int32_t process_set_id) {
    fbb_.AddElement<int32_t>(CustomCallConfig::VT_PROCESS_SET_ID, process_set_id, 0);
  }
  explicit CustomCallConfigBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  CustomCallConfigBuilder &operator=(const CustomCallConfigBuilder &);
  flatbuffers::Offset<CustomCallConfig> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<CustomCallConfig>(end);
    return o;
  }
};

inline flatbuffers::Offset<CustomCallConfig> CreateCustomCallConfig(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> tensor_name = 0,
    horovod::common::wire::DataType tensor_type = horovod::common::wire::DataType_HOROVOD_UINT8,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<TensorShape>>> input_shapes = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<TensorShape>>> output_shapes = 0,
    float prescale_factor = 0.0f,
    float postscale_factor = 0.0f,
    int32_t root_rank = 0,
    int32_t reduce_op = 0,
    int32_t process_set_id = 0) {
  CustomCallConfigBuilder builder_(_fbb);
  builder_.add_process_set_id(process_set_id);
  builder_.add_reduce_op(reduce_op);
  builder_.add_root_rank(root_rank);
  builder_.add_postscale_factor(postscale_factor);
  builder_.add_prescale_factor(prescale_factor);
  builder_.add_output_shapes(output_shapes);
  builder_.add_input_shapes(input_shapes);
  builder_.add_tensor_name(tensor_name);
  builder_.add_tensor_type(tensor_type);
  return builder_.Finish();
}

inline flatbuffers::Offset<CustomCallConfig> CreateCustomCallConfigDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *tensor_name = nullptr,
    horovod::common::wire::DataType tensor_type = horovod::common::wire::DataType_HOROVOD_UINT8,
    const std::vector<flatbuffers::Offset<TensorShape>> *input_shapes = nullptr,
    const std::vector<flatbuffers::Offset<TensorShape>> *output_shapes = nullptr,
    float prescale_factor = 0.0f,
    float postscale_factor = 0.0f,
    int32_t root_rank = 0,
    int32_t reduce_op = 0,
    int32_t process_set_id = 0) {
  auto tensor_name__ = tensor_name ? _fbb.CreateString(tensor_name) : 0;
  auto input_shapes__ = input_shapes ? _fbb.CreateVector<flatbuffers::Offset<TensorShape>>(*input_shapes) : 0;
  auto output_shapes__ = output_shapes ? _fbb.CreateVector<flatbuffers::Offset<TensorShape>>(*output_shapes) : 0;
  return horovod::xla::wire::CreateCustomCallConfig(
      _fbb,
      tensor_name__,
      tensor_type,
      input_shapes__,
      output_shapes__,
      prescale_factor,
      postscale_factor,
      root_rank,
      reduce_op,
      process_set_id);
}

}  // namespace wire
}  // namespace xla
}  // namespace horovod

#endif  // FLATBUFFERS_GENERATED_CUSTOMCALLCONFIG_HOROVOD_XLA_WIRE_H_
