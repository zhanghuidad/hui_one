// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: transform_config.proto

#ifndef PROTOBUF_transform_5fconfig_2eproto__INCLUDED
#define PROTOBUF_transform_5fconfig_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2006000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace transform {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_transform_5fconfig_2eproto();
void protobuf_AssignDesc_transform_5fconfig_2eproto();
void protobuf_ShutdownFile_transform_5fconfig_2eproto();

class ParaGimbal;

// ===================================================================

class ParaGimbal : public ::google::protobuf::Message {
 public:
  ParaGimbal();
  virtual ~ParaGimbal();

  ParaGimbal(const ParaGimbal& from);

  inline ParaGimbal& operator=(const ParaGimbal& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const ParaGimbal& default_instance();

  void Swap(ParaGimbal* other);

  // implements Message ----------------------------------------------

  ParaGimbal* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ParaGimbal& from);
  void MergeFrom(const ParaGimbal& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required double Roll_compensate = 1;
  inline bool has_roll_compensate() const;
  inline void clear_roll_compensate();
  static const int kRollCompensateFieldNumber = 1;
  inline double roll_compensate() const;
  inline void set_roll_compensate(double value);

  // required double Pitch_compensate = 2;
  inline bool has_pitch_compensate() const;
  inline void clear_pitch_compensate();
  static const int kPitchCompensateFieldNumber = 2;
  inline double pitch_compensate() const;
  inline void set_pitch_compensate(double value);

  // required double Yaw_compensate = 3;
  inline bool has_yaw_compensate() const;
  inline void clear_yaw_compensate();
  static const int kYawCompensateFieldNumber = 3;
  inline double yaw_compensate() const;
  inline void set_yaw_compensate(double value);

  // required double X_compensate = 4;
  inline bool has_x_compensate() const;
  inline void clear_x_compensate();
  static const int kXCompensateFieldNumber = 4;
  inline double x_compensate() const;
  inline void set_x_compensate(double value);

  // required double Y_compensate = 5;
  inline bool has_y_compensate() const;
  inline void clear_y_compensate();
  static const int kYCompensateFieldNumber = 5;
  inline double y_compensate() const;
  inline void set_y_compensate(double value);

  // required double Z_compensate = 6;
  inline bool has_z_compensate() const;
  inline void clear_z_compensate();
  static const int kZCompensateFieldNumber = 6;
  inline double z_compensate() const;
  inline void set_z_compensate(double value);

  // @@protoc_insertion_point(class_scope:transform.ParaGimbal)
 private:
  inline void set_has_roll_compensate();
  inline void clear_has_roll_compensate();
  inline void set_has_pitch_compensate();
  inline void clear_has_pitch_compensate();
  inline void set_has_yaw_compensate();
  inline void clear_has_yaw_compensate();
  inline void set_has_x_compensate();
  inline void clear_has_x_compensate();
  inline void set_has_y_compensate();
  inline void clear_has_y_compensate();
  inline void set_has_z_compensate();
  inline void clear_has_z_compensate();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  double roll_compensate_;
  double pitch_compensate_;
  double yaw_compensate_;
  double x_compensate_;
  double y_compensate_;
  double z_compensate_;
  friend void  protobuf_AddDesc_transform_5fconfig_2eproto();
  friend void protobuf_AssignDesc_transform_5fconfig_2eproto();
  friend void protobuf_ShutdownFile_transform_5fconfig_2eproto();

  void InitAsDefaultInstance();
  static ParaGimbal* default_instance_;
};
// ===================================================================


// ===================================================================

// ParaGimbal

// required double Roll_compensate = 1;
inline bool ParaGimbal::has_roll_compensate() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ParaGimbal::set_has_roll_compensate() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ParaGimbal::clear_has_roll_compensate() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ParaGimbal::clear_roll_compensate() {
  roll_compensate_ = 0;
  clear_has_roll_compensate();
}
inline double ParaGimbal::roll_compensate() const {
  // @@protoc_insertion_point(field_get:transform.ParaGimbal.Roll_compensate)
  return roll_compensate_;
}
inline void ParaGimbal::set_roll_compensate(double value) {
  set_has_roll_compensate();
  roll_compensate_ = value;
  // @@protoc_insertion_point(field_set:transform.ParaGimbal.Roll_compensate)
}

// required double Pitch_compensate = 2;
inline bool ParaGimbal::has_pitch_compensate() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ParaGimbal::set_has_pitch_compensate() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ParaGimbal::clear_has_pitch_compensate() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ParaGimbal::clear_pitch_compensate() {
  pitch_compensate_ = 0;
  clear_has_pitch_compensate();
}
inline double ParaGimbal::pitch_compensate() const {
  // @@protoc_insertion_point(field_get:transform.ParaGimbal.Pitch_compensate)
  return pitch_compensate_;
}
inline void ParaGimbal::set_pitch_compensate(double value) {
  set_has_pitch_compensate();
  pitch_compensate_ = value;
  // @@protoc_insertion_point(field_set:transform.ParaGimbal.Pitch_compensate)
}

// required double Yaw_compensate = 3;
inline bool ParaGimbal::has_yaw_compensate() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void ParaGimbal::set_has_yaw_compensate() {
  _has_bits_[0] |= 0x00000004u;
}
inline void ParaGimbal::clear_has_yaw_compensate() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void ParaGimbal::clear_yaw_compensate() {
  yaw_compensate_ = 0;
  clear_has_yaw_compensate();
}
inline double ParaGimbal::yaw_compensate() const {
  // @@protoc_insertion_point(field_get:transform.ParaGimbal.Yaw_compensate)
  return yaw_compensate_;
}
inline void ParaGimbal::set_yaw_compensate(double value) {
  set_has_yaw_compensate();
  yaw_compensate_ = value;
  // @@protoc_insertion_point(field_set:transform.ParaGimbal.Yaw_compensate)
}

// required double X_compensate = 4;
inline bool ParaGimbal::has_x_compensate() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void ParaGimbal::set_has_x_compensate() {
  _has_bits_[0] |= 0x00000008u;
}
inline void ParaGimbal::clear_has_x_compensate() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void ParaGimbal::clear_x_compensate() {
  x_compensate_ = 0;
  clear_has_x_compensate();
}
inline double ParaGimbal::x_compensate() const {
  // @@protoc_insertion_point(field_get:transform.ParaGimbal.X_compensate)
  return x_compensate_;
}
inline void ParaGimbal::set_x_compensate(double value) {
  set_has_x_compensate();
  x_compensate_ = value;
  // @@protoc_insertion_point(field_set:transform.ParaGimbal.X_compensate)
}

// required double Y_compensate = 5;
inline bool ParaGimbal::has_y_compensate() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void ParaGimbal::set_has_y_compensate() {
  _has_bits_[0] |= 0x00000010u;
}
inline void ParaGimbal::clear_has_y_compensate() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void ParaGimbal::clear_y_compensate() {
  y_compensate_ = 0;
  clear_has_y_compensate();
}
inline double ParaGimbal::y_compensate() const {
  // @@protoc_insertion_point(field_get:transform.ParaGimbal.Y_compensate)
  return y_compensate_;
}
inline void ParaGimbal::set_y_compensate(double value) {
  set_has_y_compensate();
  y_compensate_ = value;
  // @@protoc_insertion_point(field_set:transform.ParaGimbal.Y_compensate)
}

// required double Z_compensate = 6;
inline bool ParaGimbal::has_z_compensate() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void ParaGimbal::set_has_z_compensate() {
  _has_bits_[0] |= 0x00000020u;
}
inline void ParaGimbal::clear_has_z_compensate() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void ParaGimbal::clear_z_compensate() {
  z_compensate_ = 0;
  clear_has_z_compensate();
}
inline double ParaGimbal::z_compensate() const {
  // @@protoc_insertion_point(field_get:transform.ParaGimbal.Z_compensate)
  return z_compensate_;
}
inline void ParaGimbal::set_z_compensate(double value) {
  set_has_z_compensate();
  z_compensate_ = value;
  // @@protoc_insertion_point(field_set:transform.ParaGimbal.Z_compensate)
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace transform

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_transform_5fconfig_2eproto__INCLUDED