// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: mprpcheader.proto

#ifndef PROTOBUF_INCLUDED_mprpcheader_2eproto
#define PROTOBUF_INCLUDED_mprpcheader_2eproto

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3006001
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_mprpcheader_2eproto 

namespace protobuf_mprpcheader_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[1];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
}  // namespace protobuf_mprpcheader_2eproto
namespace mprpc {
class RpcHeader;
class RpcHeaderDefaultTypeInternal;
extern RpcHeaderDefaultTypeInternal _RpcHeader_default_instance_;
}  // namespace mprpc
namespace google {
namespace protobuf {
template<> ::mprpc::RpcHeader* Arena::CreateMaybeMessage<::mprpc::RpcHeader>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace mprpc {

// ===================================================================

class RpcHeader : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:mprpc.RpcHeader) */ {
 public:
  RpcHeader();
  virtual ~RpcHeader();

  RpcHeader(const RpcHeader& from);

  inline RpcHeader& operator=(const RpcHeader& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  RpcHeader(RpcHeader&& from) noexcept
    : RpcHeader() {
    *this = ::std::move(from);
  }

  inline RpcHeader& operator=(RpcHeader&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const RpcHeader& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const RpcHeader* internal_default_instance() {
    return reinterpret_cast<const RpcHeader*>(
               &_RpcHeader_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(RpcHeader* other);
  friend void swap(RpcHeader& a, RpcHeader& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline RpcHeader* New() const final {
    return CreateMaybeMessage<RpcHeader>(NULL);
  }

  RpcHeader* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<RpcHeader>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const RpcHeader& from);
  void MergeFrom(const RpcHeader& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(RpcHeader* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // bytes service_name = 1;
  void clear_service_name();
  static const int kServiceNameFieldNumber = 1;
  const ::std::string& service_name() const;
  void set_service_name(const ::std::string& value);
  #if LANG_CXX11
  void set_service_name(::std::string&& value);
  #endif
  void set_service_name(const char* value);
  void set_service_name(const void* value, size_t size);
  ::std::string* mutable_service_name();
  ::std::string* release_service_name();
  void set_allocated_service_name(::std::string* service_name);

  // bytes method_name = 2;
  void clear_method_name();
  static const int kMethodNameFieldNumber = 2;
  const ::std::string& method_name() const;
  void set_method_name(const ::std::string& value);
  #if LANG_CXX11
  void set_method_name(::std::string&& value);
  #endif
  void set_method_name(const char* value);
  void set_method_name(const void* value, size_t size);
  ::std::string* mutable_method_name();
  ::std::string* release_method_name();
  void set_allocated_method_name(::std::string* method_name);

  // uint32 args_size = 3;
  void clear_args_size();
  static const int kArgsSizeFieldNumber = 3;
  ::google::protobuf::uint32 args_size() const;
  void set_args_size(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:mprpc.RpcHeader)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr service_name_;
  ::google::protobuf::internal::ArenaStringPtr method_name_;
  ::google::protobuf::uint32 args_size_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_mprpcheader_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// RpcHeader

// bytes service_name = 1;
inline void RpcHeader::clear_service_name() {
  service_name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& RpcHeader::service_name() const {
  // @@protoc_insertion_point(field_get:mprpc.RpcHeader.service_name)
  return service_name_.GetNoArena();
}
inline void RpcHeader::set_service_name(const ::std::string& value) {
  
  service_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:mprpc.RpcHeader.service_name)
}
#if LANG_CXX11
inline void RpcHeader::set_service_name(::std::string&& value) {
  
  service_name_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:mprpc.RpcHeader.service_name)
}
#endif
inline void RpcHeader::set_service_name(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  service_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:mprpc.RpcHeader.service_name)
}
inline void RpcHeader::set_service_name(const void* value, size_t size) {
  
  service_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:mprpc.RpcHeader.service_name)
}
inline ::std::string* RpcHeader::mutable_service_name() {
  
  // @@protoc_insertion_point(field_mutable:mprpc.RpcHeader.service_name)
  return service_name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* RpcHeader::release_service_name() {
  // @@protoc_insertion_point(field_release:mprpc.RpcHeader.service_name)
  
  return service_name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void RpcHeader::set_allocated_service_name(::std::string* service_name) {
  if (service_name != NULL) {
    
  } else {
    
  }
  service_name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), service_name);
  // @@protoc_insertion_point(field_set_allocated:mprpc.RpcHeader.service_name)
}

// bytes method_name = 2;
inline void RpcHeader::clear_method_name() {
  method_name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& RpcHeader::method_name() const {
  // @@protoc_insertion_point(field_get:mprpc.RpcHeader.method_name)
  return method_name_.GetNoArena();
}
inline void RpcHeader::set_method_name(const ::std::string& value) {
  
  method_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:mprpc.RpcHeader.method_name)
}
#if LANG_CXX11
inline void RpcHeader::set_method_name(::std::string&& value) {
  
  method_name_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:mprpc.RpcHeader.method_name)
}
#endif
inline void RpcHeader::set_method_name(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  method_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:mprpc.RpcHeader.method_name)
}
inline void RpcHeader::set_method_name(const void* value, size_t size) {
  
  method_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:mprpc.RpcHeader.method_name)
}
inline ::std::string* RpcHeader::mutable_method_name() {
  
  // @@protoc_insertion_point(field_mutable:mprpc.RpcHeader.method_name)
  return method_name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* RpcHeader::release_method_name() {
  // @@protoc_insertion_point(field_release:mprpc.RpcHeader.method_name)
  
  return method_name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void RpcHeader::set_allocated_method_name(::std::string* method_name) {
  if (method_name != NULL) {
    
  } else {
    
  }
  method_name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), method_name);
  // @@protoc_insertion_point(field_set_allocated:mprpc.RpcHeader.method_name)
}

// uint32 args_size = 3;
inline void RpcHeader::clear_args_size() {
  args_size_ = 0u;
}
inline ::google::protobuf::uint32 RpcHeader::args_size() const {
  // @@protoc_insertion_point(field_get:mprpc.RpcHeader.args_size)
  return args_size_;
}
inline void RpcHeader::set_args_size(::google::protobuf::uint32 value) {
  
  args_size_ = value;
  // @@protoc_insertion_point(field_set:mprpc.RpcHeader.args_size)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace mprpc

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_mprpcheader_2eproto
