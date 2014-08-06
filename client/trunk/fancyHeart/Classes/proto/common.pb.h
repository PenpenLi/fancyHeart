// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: common.proto

#ifndef PROTOBUF_common_2eproto__INCLUDED
#define PROTOBUF_common_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
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

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_common_2eproto();
void protobuf_AssignDesc_common_2eproto();
void protobuf_ShutdownFile_common_2eproto();

class CommonStringObject;

// ===================================================================

class CommonStringObject : public ::google::protobuf::Message {
 public:
  CommonStringObject();
  virtual ~CommonStringObject();

  CommonStringObject(const CommonStringObject& from);

  inline CommonStringObject& operator=(const CommonStringObject& from) {
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
  static const CommonStringObject& default_instance();

  void Swap(CommonStringObject* other);

  // implements Message ----------------------------------------------

  CommonStringObject* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const CommonStringObject& from);
  void MergeFrom(const CommonStringObject& from);
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

  // required string regularStr = 1;
  inline bool has_regularstr() const;
  inline void clear_regularstr();
  static const int kRegularStrFieldNumber = 1;
  inline const ::std::string& regularstr() const;
  inline void set_regularstr(const ::std::string& value);
  inline void set_regularstr(const char* value);
  inline void set_regularstr(const char* value, size_t size);
  inline ::std::string* mutable_regularstr();
  inline ::std::string* release_regularstr();
  inline void set_allocated_regularstr(::std::string* regularstr);

  // required int32 textId = 2;
  inline bool has_textid() const;
  inline void clear_textid();
  static const int kTextIdFieldNumber = 2;
  inline ::google::protobuf::int32 textid() const;
  inline void set_textid(::google::protobuf::int32 value);

  // repeated string replaceList = 3;
  inline int replacelist_size() const;
  inline void clear_replacelist();
  static const int kReplaceListFieldNumber = 3;
  inline const ::std::string& replacelist(int index) const;
  inline ::std::string* mutable_replacelist(int index);
  inline void set_replacelist(int index, const ::std::string& value);
  inline void set_replacelist(int index, const char* value);
  inline void set_replacelist(int index, const char* value, size_t size);
  inline ::std::string* add_replacelist();
  inline void add_replacelist(const ::std::string& value);
  inline void add_replacelist(const char* value);
  inline void add_replacelist(const char* value, size_t size);
  inline const ::google::protobuf::RepeatedPtrField< ::std::string>& replacelist() const;
  inline ::google::protobuf::RepeatedPtrField< ::std::string>* mutable_replacelist();

  // @@protoc_insertion_point(class_scope:CommonStringObject)
 private:
  inline void set_has_regularstr();
  inline void clear_has_regularstr();
  inline void set_has_textid();
  inline void clear_has_textid();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* regularstr_;
  ::google::protobuf::RepeatedPtrField< ::std::string> replacelist_;
  ::google::protobuf::int32 textid_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];

  friend void  protobuf_AddDesc_common_2eproto();
  friend void protobuf_AssignDesc_common_2eproto();
  friend void protobuf_ShutdownFile_common_2eproto();

  void InitAsDefaultInstance();
  static CommonStringObject* default_instance_;
};
// ===================================================================


// ===================================================================

// CommonStringObject

// required string regularStr = 1;
inline bool CommonStringObject::has_regularstr() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void CommonStringObject::set_has_regularstr() {
  _has_bits_[0] |= 0x00000001u;
}
inline void CommonStringObject::clear_has_regularstr() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void CommonStringObject::clear_regularstr() {
  if (regularstr_ != &::google::protobuf::internal::kEmptyString) {
    regularstr_->clear();
  }
  clear_has_regularstr();
}
inline const ::std::string& CommonStringObject::regularstr() const {
  return *regularstr_;
}
inline void CommonStringObject::set_regularstr(const ::std::string& value) {
  set_has_regularstr();
  if (regularstr_ == &::google::protobuf::internal::kEmptyString) {
    regularstr_ = new ::std::string;
  }
  regularstr_->assign(value);
}
inline void CommonStringObject::set_regularstr(const char* value) {
  set_has_regularstr();
  if (regularstr_ == &::google::protobuf::internal::kEmptyString) {
    regularstr_ = new ::std::string;
  }
  regularstr_->assign(value);
}
inline void CommonStringObject::set_regularstr(const char* value, size_t size) {
  set_has_regularstr();
  if (regularstr_ == &::google::protobuf::internal::kEmptyString) {
    regularstr_ = new ::std::string;
  }
  regularstr_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* CommonStringObject::mutable_regularstr() {
  set_has_regularstr();
  if (regularstr_ == &::google::protobuf::internal::kEmptyString) {
    regularstr_ = new ::std::string;
  }
  return regularstr_;
}
inline ::std::string* CommonStringObject::release_regularstr() {
  clear_has_regularstr();
  if (regularstr_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = regularstr_;
    regularstr_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void CommonStringObject::set_allocated_regularstr(::std::string* regularstr) {
  if (regularstr_ != &::google::protobuf::internal::kEmptyString) {
    delete regularstr_;
  }
  if (regularstr) {
    set_has_regularstr();
    regularstr_ = regularstr;
  } else {
    clear_has_regularstr();
    regularstr_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// required int32 textId = 2;
inline bool CommonStringObject::has_textid() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void CommonStringObject::set_has_textid() {
  _has_bits_[0] |= 0x00000002u;
}
inline void CommonStringObject::clear_has_textid() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void CommonStringObject::clear_textid() {
  textid_ = 0;
  clear_has_textid();
}
inline ::google::protobuf::int32 CommonStringObject::textid() const {
  return textid_;
}
inline void CommonStringObject::set_textid(::google::protobuf::int32 value) {
  set_has_textid();
  textid_ = value;
}

// repeated string replaceList = 3;
inline int CommonStringObject::replacelist_size() const {
  return replacelist_.size();
}
inline void CommonStringObject::clear_replacelist() {
  replacelist_.Clear();
}
inline const ::std::string& CommonStringObject::replacelist(int index) const {
  return replacelist_.Get(index);
}
inline ::std::string* CommonStringObject::mutable_replacelist(int index) {
  return replacelist_.Mutable(index);
}
inline void CommonStringObject::set_replacelist(int index, const ::std::string& value) {
  replacelist_.Mutable(index)->assign(value);
}
inline void CommonStringObject::set_replacelist(int index, const char* value) {
  replacelist_.Mutable(index)->assign(value);
}
inline void CommonStringObject::set_replacelist(int index, const char* value, size_t size) {
  replacelist_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
}
inline ::std::string* CommonStringObject::add_replacelist() {
  return replacelist_.Add();
}
inline void CommonStringObject::add_replacelist(const ::std::string& value) {
  replacelist_.Add()->assign(value);
}
inline void CommonStringObject::add_replacelist(const char* value) {
  replacelist_.Add()->assign(value);
}
inline void CommonStringObject::add_replacelist(const char* value, size_t size) {
  replacelist_.Add()->assign(reinterpret_cast<const char*>(value), size);
}
inline const ::google::protobuf::RepeatedPtrField< ::std::string>&
CommonStringObject::replacelist() const {
  return replacelist_;
}
inline ::google::protobuf::RepeatedPtrField< ::std::string>*
CommonStringObject::mutable_replacelist() {
  return &replacelist_;
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_common_2eproto__INCLUDED