// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: obstacle_layer_setting.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "obstacle_layer_setting.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace roborts_costmap {

namespace {

const ::google::protobuf::Descriptor* ParaObstacleLayer_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  ParaObstacleLayer_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_obstacle_5flayer_5fsetting_2eproto() {
  protobuf_AddDesc_obstacle_5flayer_5fsetting_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "obstacle_layer_setting.proto");
  GOOGLE_CHECK(file != NULL);
  ParaObstacleLayer_descriptor_ = file->message_type(0);
  static const int ParaObstacleLayer_offsets_[14] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ParaObstacleLayer, observation_keep_time_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ParaObstacleLayer, expected_update_rate_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ParaObstacleLayer, min_obstacle_height_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ParaObstacleLayer, max_obstacle_height_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ParaObstacleLayer, obstacle_range_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ParaObstacleLayer, raytrace_range_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ParaObstacleLayer, transform_tolerance_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ParaObstacleLayer, topic_string_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ParaObstacleLayer, sensor_frame_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ParaObstacleLayer, inf_is_valid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ParaObstacleLayer, clearing_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ParaObstacleLayer, marking_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ParaObstacleLayer, footprint_clearing_enabled_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ParaObstacleLayer, is_debug_),
  };
  ParaObstacleLayer_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      ParaObstacleLayer_descriptor_,
      ParaObstacleLayer::default_instance_,
      ParaObstacleLayer_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ParaObstacleLayer, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ParaObstacleLayer, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(ParaObstacleLayer));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_obstacle_5flayer_5fsetting_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    ParaObstacleLayer_descriptor_, &ParaObstacleLayer::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_obstacle_5flayer_5fsetting_2eproto() {
  delete ParaObstacleLayer::default_instance_;
  delete ParaObstacleLayer_reflection_;
}

void protobuf_AddDesc_obstacle_5flayer_5fsetting_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\034obstacle_layer_setting.proto\022\017roborts_"
    "costmap\"\362\002\n\021ParaObstacleLayer\022\035\n\025observa"
    "tion_keep_time\030\001 \002(\001\022\034\n\024expected_update_"
    "rate\030\002 \002(\001\022\033\n\023min_obstacle_height\030\003 \002(\001\022"
    "\033\n\023max_obstacle_height\030\004 \002(\001\022\026\n\016obstacle"
    "_range\030\005 \002(\001\022\026\n\016raytrace_range\030\006 \002(\001\022\033\n\023"
    "transform_tolerance\030\007 \002(\001\022\024\n\014topic_strin"
    "g\030\010 \002(\t\022\024\n\014sensor_frame\030\t \002(\t\022\024\n\014inf_is_"
    "valid\030\n \002(\010\022\020\n\010clearing\030\013 \002(\010\022\017\n\007marking"
    "\030\014 \002(\010\022\"\n\032footprint_clearing_enabled\030\r \002"
    "(\010\022\020\n\010is_debug\030\016 \002(\010", 420);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "obstacle_layer_setting.proto", &protobuf_RegisterTypes);
  ParaObstacleLayer::default_instance_ = new ParaObstacleLayer();
  ParaObstacleLayer::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_obstacle_5flayer_5fsetting_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_obstacle_5flayer_5fsetting_2eproto {
  StaticDescriptorInitializer_obstacle_5flayer_5fsetting_2eproto() {
    protobuf_AddDesc_obstacle_5flayer_5fsetting_2eproto();
  }
} static_descriptor_initializer_obstacle_5flayer_5fsetting_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int ParaObstacleLayer::kObservationKeepTimeFieldNumber;
const int ParaObstacleLayer::kExpectedUpdateRateFieldNumber;
const int ParaObstacleLayer::kMinObstacleHeightFieldNumber;
const int ParaObstacleLayer::kMaxObstacleHeightFieldNumber;
const int ParaObstacleLayer::kObstacleRangeFieldNumber;
const int ParaObstacleLayer::kRaytraceRangeFieldNumber;
const int ParaObstacleLayer::kTransformToleranceFieldNumber;
const int ParaObstacleLayer::kTopicStringFieldNumber;
const int ParaObstacleLayer::kSensorFrameFieldNumber;
const int ParaObstacleLayer::kInfIsValidFieldNumber;
const int ParaObstacleLayer::kClearingFieldNumber;
const int ParaObstacleLayer::kMarkingFieldNumber;
const int ParaObstacleLayer::kFootprintClearingEnabledFieldNumber;
const int ParaObstacleLayer::kIsDebugFieldNumber;
#endif  // !_MSC_VER

ParaObstacleLayer::ParaObstacleLayer()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:roborts_costmap.ParaObstacleLayer)
}

void ParaObstacleLayer::InitAsDefaultInstance() {
}

ParaObstacleLayer::ParaObstacleLayer(const ParaObstacleLayer& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:roborts_costmap.ParaObstacleLayer)
}

void ParaObstacleLayer::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  observation_keep_time_ = 0;
  expected_update_rate_ = 0;
  min_obstacle_height_ = 0;
  max_obstacle_height_ = 0;
  obstacle_range_ = 0;
  raytrace_range_ = 0;
  transform_tolerance_ = 0;
  topic_string_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  sensor_frame_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  inf_is_valid_ = false;
  clearing_ = false;
  marking_ = false;
  footprint_clearing_enabled_ = false;
  is_debug_ = false;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ParaObstacleLayer::~ParaObstacleLayer() {
  // @@protoc_insertion_point(destructor:roborts_costmap.ParaObstacleLayer)
  SharedDtor();
}

void ParaObstacleLayer::SharedDtor() {
  if (topic_string_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete topic_string_;
  }
  if (sensor_frame_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete sensor_frame_;
  }
  if (this != default_instance_) {
  }
}

void ParaObstacleLayer::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ParaObstacleLayer::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ParaObstacleLayer_descriptor_;
}

const ParaObstacleLayer& ParaObstacleLayer::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_obstacle_5flayer_5fsetting_2eproto();
  return *default_instance_;
}

ParaObstacleLayer* ParaObstacleLayer::default_instance_ = NULL;

ParaObstacleLayer* ParaObstacleLayer::New() const {
  return new ParaObstacleLayer;
}

void ParaObstacleLayer::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<ParaObstacleLayer*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  if (_has_bits_[0 / 32] & 255) {
    ZR_(observation_keep_time_, transform_tolerance_);
    if (has_topic_string()) {
      if (topic_string_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        topic_string_->clear();
      }
    }
  }
  if (_has_bits_[8 / 32] & 16128) {
    ZR_(inf_is_valid_, is_debug_);
    if (has_sensor_frame()) {
      if (sensor_frame_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        sensor_frame_->clear();
      }
    }
  }

#undef OFFSET_OF_FIELD_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool ParaObstacleLayer::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:roborts_costmap.ParaObstacleLayer)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required double observation_keep_time = 1;
      case 1: {
        if (tag == 9) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &observation_keep_time_)));
          set_has_observation_keep_time();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(17)) goto parse_expected_update_rate;
        break;
      }

      // required double expected_update_rate = 2;
      case 2: {
        if (tag == 17) {
         parse_expected_update_rate:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &expected_update_rate_)));
          set_has_expected_update_rate();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(25)) goto parse_min_obstacle_height;
        break;
      }

      // required double min_obstacle_height = 3;
      case 3: {
        if (tag == 25) {
         parse_min_obstacle_height:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &min_obstacle_height_)));
          set_has_min_obstacle_height();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(33)) goto parse_max_obstacle_height;
        break;
      }

      // required double max_obstacle_height = 4;
      case 4: {
        if (tag == 33) {
         parse_max_obstacle_height:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &max_obstacle_height_)));
          set_has_max_obstacle_height();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(41)) goto parse_obstacle_range;
        break;
      }

      // required double obstacle_range = 5;
      case 5: {
        if (tag == 41) {
         parse_obstacle_range:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &obstacle_range_)));
          set_has_obstacle_range();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(49)) goto parse_raytrace_range;
        break;
      }

      // required double raytrace_range = 6;
      case 6: {
        if (tag == 49) {
         parse_raytrace_range:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &raytrace_range_)));
          set_has_raytrace_range();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(57)) goto parse_transform_tolerance;
        break;
      }

      // required double transform_tolerance = 7;
      case 7: {
        if (tag == 57) {
         parse_transform_tolerance:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &transform_tolerance_)));
          set_has_transform_tolerance();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(66)) goto parse_topic_string;
        break;
      }

      // required string topic_string = 8;
      case 8: {
        if (tag == 66) {
         parse_topic_string:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_topic_string()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->topic_string().data(), this->topic_string().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "topic_string");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(74)) goto parse_sensor_frame;
        break;
      }

      // required string sensor_frame = 9;
      case 9: {
        if (tag == 74) {
         parse_sensor_frame:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_sensor_frame()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->sensor_frame().data(), this->sensor_frame().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "sensor_frame");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(80)) goto parse_inf_is_valid;
        break;
      }

      // required bool inf_is_valid = 10;
      case 10: {
        if (tag == 80) {
         parse_inf_is_valid:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &inf_is_valid_)));
          set_has_inf_is_valid();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(88)) goto parse_clearing;
        break;
      }

      // required bool clearing = 11;
      case 11: {
        if (tag == 88) {
         parse_clearing:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &clearing_)));
          set_has_clearing();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(96)) goto parse_marking;
        break;
      }

      // required bool marking = 12;
      case 12: {
        if (tag == 96) {
         parse_marking:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &marking_)));
          set_has_marking();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(104)) goto parse_footprint_clearing_enabled;
        break;
      }

      // required bool footprint_clearing_enabled = 13;
      case 13: {
        if (tag == 104) {
         parse_footprint_clearing_enabled:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &footprint_clearing_enabled_)));
          set_has_footprint_clearing_enabled();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(112)) goto parse_is_debug;
        break;
      }

      // required bool is_debug = 14;
      case 14: {
        if (tag == 112) {
         parse_is_debug:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &is_debug_)));
          set_has_is_debug();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:roborts_costmap.ParaObstacleLayer)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:roborts_costmap.ParaObstacleLayer)
  return false;
#undef DO_
}

void ParaObstacleLayer::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:roborts_costmap.ParaObstacleLayer)
  // required double observation_keep_time = 1;
  if (has_observation_keep_time()) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(1, this->observation_keep_time(), output);
  }

  // required double expected_update_rate = 2;
  if (has_expected_update_rate()) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(2, this->expected_update_rate(), output);
  }

  // required double min_obstacle_height = 3;
  if (has_min_obstacle_height()) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(3, this->min_obstacle_height(), output);
  }

  // required double max_obstacle_height = 4;
  if (has_max_obstacle_height()) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(4, this->max_obstacle_height(), output);
  }

  // required double obstacle_range = 5;
  if (has_obstacle_range()) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(5, this->obstacle_range(), output);
  }

  // required double raytrace_range = 6;
  if (has_raytrace_range()) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(6, this->raytrace_range(), output);
  }

  // required double transform_tolerance = 7;
  if (has_transform_tolerance()) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(7, this->transform_tolerance(), output);
  }

  // required string topic_string = 8;
  if (has_topic_string()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->topic_string().data(), this->topic_string().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "topic_string");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      8, this->topic_string(), output);
  }

  // required string sensor_frame = 9;
  if (has_sensor_frame()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->sensor_frame().data(), this->sensor_frame().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "sensor_frame");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      9, this->sensor_frame(), output);
  }

  // required bool inf_is_valid = 10;
  if (has_inf_is_valid()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(10, this->inf_is_valid(), output);
  }

  // required bool clearing = 11;
  if (has_clearing()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(11, this->clearing(), output);
  }

  // required bool marking = 12;
  if (has_marking()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(12, this->marking(), output);
  }

  // required bool footprint_clearing_enabled = 13;
  if (has_footprint_clearing_enabled()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(13, this->footprint_clearing_enabled(), output);
  }

  // required bool is_debug = 14;
  if (has_is_debug()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(14, this->is_debug(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:roborts_costmap.ParaObstacleLayer)
}

::google::protobuf::uint8* ParaObstacleLayer::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:roborts_costmap.ParaObstacleLayer)
  // required double observation_keep_time = 1;
  if (has_observation_keep_time()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(1, this->observation_keep_time(), target);
  }

  // required double expected_update_rate = 2;
  if (has_expected_update_rate()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(2, this->expected_update_rate(), target);
  }

  // required double min_obstacle_height = 3;
  if (has_min_obstacle_height()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(3, this->min_obstacle_height(), target);
  }

  // required double max_obstacle_height = 4;
  if (has_max_obstacle_height()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(4, this->max_obstacle_height(), target);
  }

  // required double obstacle_range = 5;
  if (has_obstacle_range()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(5, this->obstacle_range(), target);
  }

  // required double raytrace_range = 6;
  if (has_raytrace_range()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(6, this->raytrace_range(), target);
  }

  // required double transform_tolerance = 7;
  if (has_transform_tolerance()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(7, this->transform_tolerance(), target);
  }

  // required string topic_string = 8;
  if (has_topic_string()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->topic_string().data(), this->topic_string().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "topic_string");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        8, this->topic_string(), target);
  }

  // required string sensor_frame = 9;
  if (has_sensor_frame()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->sensor_frame().data(), this->sensor_frame().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "sensor_frame");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        9, this->sensor_frame(), target);
  }

  // required bool inf_is_valid = 10;
  if (has_inf_is_valid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(10, this->inf_is_valid(), target);
  }

  // required bool clearing = 11;
  if (has_clearing()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(11, this->clearing(), target);
  }

  // required bool marking = 12;
  if (has_marking()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(12, this->marking(), target);
  }

  // required bool footprint_clearing_enabled = 13;
  if (has_footprint_clearing_enabled()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(13, this->footprint_clearing_enabled(), target);
  }

  // required bool is_debug = 14;
  if (has_is_debug()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(14, this->is_debug(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:roborts_costmap.ParaObstacleLayer)
  return target;
}

int ParaObstacleLayer::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required double observation_keep_time = 1;
    if (has_observation_keep_time()) {
      total_size += 1 + 8;
    }

    // required double expected_update_rate = 2;
    if (has_expected_update_rate()) {
      total_size += 1 + 8;
    }

    // required double min_obstacle_height = 3;
    if (has_min_obstacle_height()) {
      total_size += 1 + 8;
    }

    // required double max_obstacle_height = 4;
    if (has_max_obstacle_height()) {
      total_size += 1 + 8;
    }

    // required double obstacle_range = 5;
    if (has_obstacle_range()) {
      total_size += 1 + 8;
    }

    // required double raytrace_range = 6;
    if (has_raytrace_range()) {
      total_size += 1 + 8;
    }

    // required double transform_tolerance = 7;
    if (has_transform_tolerance()) {
      total_size += 1 + 8;
    }

    // required string topic_string = 8;
    if (has_topic_string()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->topic_string());
    }

  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    // required string sensor_frame = 9;
    if (has_sensor_frame()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->sensor_frame());
    }

    // required bool inf_is_valid = 10;
    if (has_inf_is_valid()) {
      total_size += 1 + 1;
    }

    // required bool clearing = 11;
    if (has_clearing()) {
      total_size += 1 + 1;
    }

    // required bool marking = 12;
    if (has_marking()) {
      total_size += 1 + 1;
    }

    // required bool footprint_clearing_enabled = 13;
    if (has_footprint_clearing_enabled()) {
      total_size += 1 + 1;
    }

    // required bool is_debug = 14;
    if (has_is_debug()) {
      total_size += 1 + 1;
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void ParaObstacleLayer::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const ParaObstacleLayer* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const ParaObstacleLayer*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void ParaObstacleLayer::MergeFrom(const ParaObstacleLayer& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_observation_keep_time()) {
      set_observation_keep_time(from.observation_keep_time());
    }
    if (from.has_expected_update_rate()) {
      set_expected_update_rate(from.expected_update_rate());
    }
    if (from.has_min_obstacle_height()) {
      set_min_obstacle_height(from.min_obstacle_height());
    }
    if (from.has_max_obstacle_height()) {
      set_max_obstacle_height(from.max_obstacle_height());
    }
    if (from.has_obstacle_range()) {
      set_obstacle_range(from.obstacle_range());
    }
    if (from.has_raytrace_range()) {
      set_raytrace_range(from.raytrace_range());
    }
    if (from.has_transform_tolerance()) {
      set_transform_tolerance(from.transform_tolerance());
    }
    if (from.has_topic_string()) {
      set_topic_string(from.topic_string());
    }
  }
  if (from._has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    if (from.has_sensor_frame()) {
      set_sensor_frame(from.sensor_frame());
    }
    if (from.has_inf_is_valid()) {
      set_inf_is_valid(from.inf_is_valid());
    }
    if (from.has_clearing()) {
      set_clearing(from.clearing());
    }
    if (from.has_marking()) {
      set_marking(from.marking());
    }
    if (from.has_footprint_clearing_enabled()) {
      set_footprint_clearing_enabled(from.footprint_clearing_enabled());
    }
    if (from.has_is_debug()) {
      set_is_debug(from.is_debug());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void ParaObstacleLayer::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ParaObstacleLayer::CopyFrom(const ParaObstacleLayer& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ParaObstacleLayer::IsInitialized() const {
  if ((_has_bits_[0] & 0x00003fff) != 0x00003fff) return false;

  return true;
}

void ParaObstacleLayer::Swap(ParaObstacleLayer* other) {
  if (other != this) {
    std::swap(observation_keep_time_, other->observation_keep_time_);
    std::swap(expected_update_rate_, other->expected_update_rate_);
    std::swap(min_obstacle_height_, other->min_obstacle_height_);
    std::swap(max_obstacle_height_, other->max_obstacle_height_);
    std::swap(obstacle_range_, other->obstacle_range_);
    std::swap(raytrace_range_, other->raytrace_range_);
    std::swap(transform_tolerance_, other->transform_tolerance_);
    std::swap(topic_string_, other->topic_string_);
    std::swap(sensor_frame_, other->sensor_frame_);
    std::swap(inf_is_valid_, other->inf_is_valid_);
    std::swap(clearing_, other->clearing_);
    std::swap(marking_, other->marking_);
    std::swap(footprint_clearing_enabled_, other->footprint_clearing_enabled_);
    std::swap(is_debug_, other->is_debug_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata ParaObstacleLayer::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = ParaObstacleLayer_descriptor_;
  metadata.reflection = ParaObstacleLayer_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace roborts_costmap

// @@protoc_insertion_point(global_scope)
