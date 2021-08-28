// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: http_service.proto

#ifndef PROTOBUF_http_5fservice_2eproto__INCLUDED
#define PROTOBUF_http_5fservice_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3001000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3001000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/service.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace nlper {

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_http_5fservice_2eproto();
void protobuf_InitDefaults_http_5fservice_2eproto();
void protobuf_AssignDesc_http_5fservice_2eproto();
void protobuf_ShutdownFile_http_5fservice_2eproto();

class HttpRequest;
class HttpResponse;

// ===================================================================

class HttpRequest : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:nlper.HttpRequest) */ {
 public:
  HttpRequest();
  virtual ~HttpRequest();

  HttpRequest(const HttpRequest& from);

  inline HttpRequest& operator=(const HttpRequest& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const HttpRequest& default_instance();

  static const HttpRequest* internal_default_instance();

  void Swap(HttpRequest* other);

  // implements Message ----------------------------------------------

  inline HttpRequest* New() const { return New(NULL); }

  HttpRequest* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const HttpRequest& from);
  void MergeFrom(const HttpRequest& from);
  void Clear();
  bool IsInitialized() const;

  size_t ByteSizeLong() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const {
    return InternalSerializeWithCachedSizesToArray(false, output);
  }
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(HttpRequest* other);
  void UnsafeMergeFrom(const HttpRequest& from);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // @@protoc_insertion_point(class_scope:nlper.HttpRequest)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  friend void  protobuf_InitDefaults_http_5fservice_2eproto_impl();
  friend void  protobuf_AddDesc_http_5fservice_2eproto_impl();
  friend void protobuf_AssignDesc_http_5fservice_2eproto();
  friend void protobuf_ShutdownFile_http_5fservice_2eproto();

  void InitAsDefaultInstance();
};
extern ::google::protobuf::internal::ExplicitlyConstructed<HttpRequest> HttpRequest_default_instance_;

// -------------------------------------------------------------------

class HttpResponse : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:nlper.HttpResponse) */ {
 public:
  HttpResponse();
  virtual ~HttpResponse();

  HttpResponse(const HttpResponse& from);

  inline HttpResponse& operator=(const HttpResponse& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const HttpResponse& default_instance();

  static const HttpResponse* internal_default_instance();

  void Swap(HttpResponse* other);

  // implements Message ----------------------------------------------

  inline HttpResponse* New() const { return New(NULL); }

  HttpResponse* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const HttpResponse& from);
  void MergeFrom(const HttpResponse& from);
  void Clear();
  bool IsInitialized() const;

  size_t ByteSizeLong() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const {
    return InternalSerializeWithCachedSizesToArray(false, output);
  }
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(HttpResponse* other);
  void UnsafeMergeFrom(const HttpResponse& from);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // @@protoc_insertion_point(class_scope:nlper.HttpResponse)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  friend void  protobuf_InitDefaults_http_5fservice_2eproto_impl();
  friend void  protobuf_AddDesc_http_5fservice_2eproto_impl();
  friend void protobuf_AssignDesc_http_5fservice_2eproto();
  friend void protobuf_ShutdownFile_http_5fservice_2eproto();

  void InitAsDefaultInstance();
};
extern ::google::protobuf::internal::ExplicitlyConstructed<HttpResponse> HttpResponse_default_instance_;

// ===================================================================

class HttpService_Stub;

class HttpService : public ::google::protobuf::Service {
 protected:
  // This class should be treated as an abstract interface.
  inline HttpService() {};
 public:
  virtual ~HttpService();

  typedef HttpService_Stub Stub;

  static const ::google::protobuf::ServiceDescriptor* descriptor();

  virtual void run_semtopic(::google::protobuf::RpcController* controller,
                       const ::nlper::HttpRequest* request,
                       ::nlper::HttpResponse* response,
                       ::google::protobuf::Closure* done);
  virtual void run_qdmatch(::google::protobuf::RpcController* controller,
                       const ::nlper::HttpRequest* request,
                       ::nlper::HttpResponse* response,
                       ::google::protobuf::Closure* done);
  virtual void run_ddmatch(::google::protobuf::RpcController* controller,
                       const ::nlper::HttpRequest* request,
                       ::nlper::HttpResponse* response,
                       ::google::protobuf::Closure* done);

  // implements Service ----------------------------------------------

  const ::google::protobuf::ServiceDescriptor* GetDescriptor();
  void CallMethod(const ::google::protobuf::MethodDescriptor* method,
                  ::google::protobuf::RpcController* controller,
                  const ::google::protobuf::Message* request,
                  ::google::protobuf::Message* response,
                  ::google::protobuf::Closure* done);
  const ::google::protobuf::Message& GetRequestPrototype(
    const ::google::protobuf::MethodDescriptor* method) const;
  const ::google::protobuf::Message& GetResponsePrototype(
    const ::google::protobuf::MethodDescriptor* method) const;

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(HttpService);
};

class HttpService_Stub : public HttpService {
 public:
  HttpService_Stub(::google::protobuf::RpcChannel* channel);
  HttpService_Stub(::google::protobuf::RpcChannel* channel,
                   ::google::protobuf::Service::ChannelOwnership ownership);
  ~HttpService_Stub();

  inline ::google::protobuf::RpcChannel* channel() { return channel_; }

  // implements HttpService ------------------------------------------

  void run_semtopic(::google::protobuf::RpcController* controller,
                       const ::nlper::HttpRequest* request,
                       ::nlper::HttpResponse* response,
                       ::google::protobuf::Closure* done);
  void run_qdmatch(::google::protobuf::RpcController* controller,
                       const ::nlper::HttpRequest* request,
                       ::nlper::HttpResponse* response,
                       ::google::protobuf::Closure* done);
  void run_ddmatch(::google::protobuf::RpcController* controller,
                       const ::nlper::HttpRequest* request,
                       ::nlper::HttpResponse* response,
                       ::google::protobuf::Closure* done);
 private:
  ::google::protobuf::RpcChannel* channel_;
  bool owns_channel_;
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(HttpService_Stub);
};


// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// HttpRequest

inline const HttpRequest* HttpRequest::internal_default_instance() {
  return &HttpRequest_default_instance_.get();
}
// -------------------------------------------------------------------

// HttpResponse

inline const HttpResponse* HttpResponse::internal_default_instance() {
  return &HttpResponse_default_instance_.get();
}
#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace nlper

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_http_5fservice_2eproto__INCLUDED
