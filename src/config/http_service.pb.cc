// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: http_service.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "http_service.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace nlper {

namespace {

const ::google::protobuf::Descriptor* HttpRequest_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  HttpRequest_reflection_ = NULL;
const ::google::protobuf::Descriptor* HttpResponse_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  HttpResponse_reflection_ = NULL;
const ::google::protobuf::ServiceDescriptor* HttpService_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_http_5fservice_2eproto() GOOGLE_ATTRIBUTE_COLD;
void protobuf_AssignDesc_http_5fservice_2eproto() {
  protobuf_AddDesc_http_5fservice_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "http_service.proto");
  GOOGLE_CHECK(file != NULL);
  HttpRequest_descriptor_ = file->message_type(0);
  static const int HttpRequest_offsets_[1] = {
  };
  HttpRequest_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      HttpRequest_descriptor_,
      HttpRequest::internal_default_instance(),
      HttpRequest_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(HttpRequest, _has_bits_),
      -1,
      -1,
      sizeof(HttpRequest),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(HttpRequest, _internal_metadata_));
  HttpResponse_descriptor_ = file->message_type(1);
  static const int HttpResponse_offsets_[1] = {
  };
  HttpResponse_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      HttpResponse_descriptor_,
      HttpResponse::internal_default_instance(),
      HttpResponse_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(HttpResponse, _has_bits_),
      -1,
      -1,
      sizeof(HttpResponse),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(HttpResponse, _internal_metadata_));
  HttpService_descriptor_ = file->service(0);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_http_5fservice_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      HttpRequest_descriptor_, HttpRequest::internal_default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      HttpResponse_descriptor_, HttpResponse::internal_default_instance());
}

}  // namespace

void protobuf_ShutdownFile_http_5fservice_2eproto() {
  HttpRequest_default_instance_.Shutdown();
  delete HttpRequest_reflection_;
  HttpResponse_default_instance_.Shutdown();
  delete HttpResponse_reflection_;
}

void protobuf_InitDefaults_http_5fservice_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  HttpRequest_default_instance_.DefaultConstruct();
  HttpResponse_default_instance_.DefaultConstruct();
  HttpRequest_default_instance_.get_mutable()->InitAsDefaultInstance();
  HttpResponse_default_instance_.get_mutable()->InitAsDefaultInstance();
}

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_InitDefaults_http_5fservice_2eproto_once_);
void protobuf_InitDefaults_http_5fservice_2eproto() {
  ::google::protobuf::GoogleOnceInit(&protobuf_InitDefaults_http_5fservice_2eproto_once_,
                 &protobuf_InitDefaults_http_5fservice_2eproto_impl);
}
void protobuf_AddDesc_http_5fservice_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  protobuf_InitDefaults_http_5fservice_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\022http_service.proto\022\005nlper\"\r\n\013HttpReque"
    "st\"\016\n\014HttpResponse2\266\001\n\013HttpService\0227\n\014ru"
    "n_semtopic\022\022.nlper.HttpRequest\032\023.nlper.H"
    "ttpResponse\0226\n\013run_qdmatch\022\022.nlper.HttpR"
    "equest\032\023.nlper.HttpResponse\0226\n\013run_ddmat"
    "ch\022\022.nlper.HttpRequest\032\023.nlper.HttpRespo"
    "nseB\003\200\001\001", 248);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "http_service.proto", &protobuf_RegisterTypes);
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_http_5fservice_2eproto);
}

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AddDesc_http_5fservice_2eproto_once_);
void protobuf_AddDesc_http_5fservice_2eproto() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AddDesc_http_5fservice_2eproto_once_,
                 &protobuf_AddDesc_http_5fservice_2eproto_impl);
}
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_http_5fservice_2eproto {
  StaticDescriptorInitializer_http_5fservice_2eproto() {
    protobuf_AddDesc_http_5fservice_2eproto();
  }
} static_descriptor_initializer_http_5fservice_2eproto_;

namespace {

static void MergeFromFail(int line) GOOGLE_ATTRIBUTE_COLD GOOGLE_ATTRIBUTE_NORETURN;
static void MergeFromFail(int line) {
  ::google::protobuf::internal::MergeFromFail(__FILE__, line);
}

}  // namespace


// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

HttpRequest::HttpRequest()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (this != internal_default_instance()) protobuf_InitDefaults_http_5fservice_2eproto();
  SharedCtor();
  // @@protoc_insertion_point(constructor:nlper.HttpRequest)
}

void HttpRequest::InitAsDefaultInstance() {
}

HttpRequest::HttpRequest(const HttpRequest& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  UnsafeMergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:nlper.HttpRequest)
}

void HttpRequest::SharedCtor() {
  _cached_size_ = 0;
}

HttpRequest::~HttpRequest() {
  // @@protoc_insertion_point(destructor:nlper.HttpRequest)
  SharedDtor();
}

void HttpRequest::SharedDtor() {
}

void HttpRequest::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* HttpRequest::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return HttpRequest_descriptor_;
}

const HttpRequest& HttpRequest::default_instance() {
  protobuf_InitDefaults_http_5fservice_2eproto();
  return *internal_default_instance();
}

::google::protobuf::internal::ExplicitlyConstructed<HttpRequest> HttpRequest_default_instance_;

HttpRequest* HttpRequest::New(::google::protobuf::Arena* arena) const {
  HttpRequest* n = new HttpRequest;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void HttpRequest::Clear() {
// @@protoc_insertion_point(message_clear_start:nlper.HttpRequest)
  _has_bits_.Clear();
  if (_internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->Clear();
  }
}

bool HttpRequest::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:nlper.HttpRequest)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
  handle_unusual:
    if (tag == 0 ||
        ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
        ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
      goto success;
    }
    DO_(::google::protobuf::internal::WireFormat::SkipField(
          input, tag, mutable_unknown_fields()));
  }
success:
  // @@protoc_insertion_point(parse_success:nlper.HttpRequest)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:nlper.HttpRequest)
  return false;
#undef DO_
}

void HttpRequest::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:nlper.HttpRequest)
  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:nlper.HttpRequest)
}

::google::protobuf::uint8* HttpRequest::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:nlper.HttpRequest)
  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:nlper.HttpRequest)
  return target;
}

size_t HttpRequest::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:nlper.HttpRequest)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void HttpRequest::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:nlper.HttpRequest)
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  const HttpRequest* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const HttpRequest>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:nlper.HttpRequest)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:nlper.HttpRequest)
    UnsafeMergeFrom(*source);
  }
}

void HttpRequest::MergeFrom(const HttpRequest& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:nlper.HttpRequest)
  if (GOOGLE_PREDICT_TRUE(&from != this)) {
    UnsafeMergeFrom(from);
  } else {
    MergeFromFail(__LINE__);
  }
}

void HttpRequest::UnsafeMergeFrom(const HttpRequest& from) {
  GOOGLE_DCHECK(&from != this);
  if (from._internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::UnknownFieldSet::MergeToInternalMetdata(
      from.unknown_fields(), &_internal_metadata_);
  }
}

void HttpRequest::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:nlper.HttpRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void HttpRequest::CopyFrom(const HttpRequest& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:nlper.HttpRequest)
  if (&from == this) return;
  Clear();
  UnsafeMergeFrom(from);
}

bool HttpRequest::IsInitialized() const {

  return true;
}

void HttpRequest::Swap(HttpRequest* other) {
  if (other == this) return;
  InternalSwap(other);
}
void HttpRequest::InternalSwap(HttpRequest* other) {
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata HttpRequest::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = HttpRequest_descriptor_;
  metadata.reflection = HttpRequest_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// HttpRequest

inline const HttpRequest* HttpRequest::internal_default_instance() {
  return &HttpRequest_default_instance_.get();
}
#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

HttpResponse::HttpResponse()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (this != internal_default_instance()) protobuf_InitDefaults_http_5fservice_2eproto();
  SharedCtor();
  // @@protoc_insertion_point(constructor:nlper.HttpResponse)
}

void HttpResponse::InitAsDefaultInstance() {
}

HttpResponse::HttpResponse(const HttpResponse& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  UnsafeMergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:nlper.HttpResponse)
}

void HttpResponse::SharedCtor() {
  _cached_size_ = 0;
}

HttpResponse::~HttpResponse() {
  // @@protoc_insertion_point(destructor:nlper.HttpResponse)
  SharedDtor();
}

void HttpResponse::SharedDtor() {
}

void HttpResponse::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* HttpResponse::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return HttpResponse_descriptor_;
}

const HttpResponse& HttpResponse::default_instance() {
  protobuf_InitDefaults_http_5fservice_2eproto();
  return *internal_default_instance();
}

::google::protobuf::internal::ExplicitlyConstructed<HttpResponse> HttpResponse_default_instance_;

HttpResponse* HttpResponse::New(::google::protobuf::Arena* arena) const {
  HttpResponse* n = new HttpResponse;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void HttpResponse::Clear() {
// @@protoc_insertion_point(message_clear_start:nlper.HttpResponse)
  _has_bits_.Clear();
  if (_internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->Clear();
  }
}

bool HttpResponse::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:nlper.HttpResponse)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
  handle_unusual:
    if (tag == 0 ||
        ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
        ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
      goto success;
    }
    DO_(::google::protobuf::internal::WireFormat::SkipField(
          input, tag, mutable_unknown_fields()));
  }
success:
  // @@protoc_insertion_point(parse_success:nlper.HttpResponse)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:nlper.HttpResponse)
  return false;
#undef DO_
}

void HttpResponse::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:nlper.HttpResponse)
  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:nlper.HttpResponse)
}

::google::protobuf::uint8* HttpResponse::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:nlper.HttpResponse)
  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:nlper.HttpResponse)
  return target;
}

size_t HttpResponse::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:nlper.HttpResponse)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void HttpResponse::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:nlper.HttpResponse)
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  const HttpResponse* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const HttpResponse>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:nlper.HttpResponse)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:nlper.HttpResponse)
    UnsafeMergeFrom(*source);
  }
}

void HttpResponse::MergeFrom(const HttpResponse& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:nlper.HttpResponse)
  if (GOOGLE_PREDICT_TRUE(&from != this)) {
    UnsafeMergeFrom(from);
  } else {
    MergeFromFail(__LINE__);
  }
}

void HttpResponse::UnsafeMergeFrom(const HttpResponse& from) {
  GOOGLE_DCHECK(&from != this);
  if (from._internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::UnknownFieldSet::MergeToInternalMetdata(
      from.unknown_fields(), &_internal_metadata_);
  }
}

void HttpResponse::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:nlper.HttpResponse)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void HttpResponse::CopyFrom(const HttpResponse& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:nlper.HttpResponse)
  if (&from == this) return;
  Clear();
  UnsafeMergeFrom(from);
}

bool HttpResponse::IsInitialized() const {

  return true;
}

void HttpResponse::Swap(HttpResponse* other) {
  if (other == this) return;
  InternalSwap(other);
}
void HttpResponse::InternalSwap(HttpResponse* other) {
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata HttpResponse::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = HttpResponse_descriptor_;
  metadata.reflection = HttpResponse_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// HttpResponse

inline const HttpResponse* HttpResponse::internal_default_instance() {
  return &HttpResponse_default_instance_.get();
}
#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// ===================================================================

HttpService::~HttpService() {}

const ::google::protobuf::ServiceDescriptor* HttpService::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return HttpService_descriptor_;
}

const ::google::protobuf::ServiceDescriptor* HttpService::GetDescriptor() {
  protobuf_AssignDescriptorsOnce();
  return HttpService_descriptor_;
}

void HttpService::run_semtopic(::google::protobuf::RpcController* controller,
                         const ::nlper::HttpRequest*,
                         ::nlper::HttpResponse*,
                         ::google::protobuf::Closure* done) {
  controller->SetFailed("Method run_semtopic() not implemented.");
  done->Run();
}

void HttpService::run_qdmatch(::google::protobuf::RpcController* controller,
                         const ::nlper::HttpRequest*,
                         ::nlper::HttpResponse*,
                         ::google::protobuf::Closure* done) {
  controller->SetFailed("Method run_qdmatch() not implemented.");
  done->Run();
}

void HttpService::run_ddmatch(::google::protobuf::RpcController* controller,
                         const ::nlper::HttpRequest*,
                         ::nlper::HttpResponse*,
                         ::google::protobuf::Closure* done) {
  controller->SetFailed("Method run_ddmatch() not implemented.");
  done->Run();
}

void HttpService::CallMethod(const ::google::protobuf::MethodDescriptor* method,
                             ::google::protobuf::RpcController* controller,
                             const ::google::protobuf::Message* request,
                             ::google::protobuf::Message* response,
                             ::google::protobuf::Closure* done) {
  GOOGLE_DCHECK_EQ(method->service(), HttpService_descriptor_);
  switch(method->index()) {
    case 0:
      run_semtopic(controller,
             ::google::protobuf::down_cast<const ::nlper::HttpRequest*>(request),
             ::google::protobuf::down_cast< ::nlper::HttpResponse*>(response),
             done);
      break;
    case 1:
      run_qdmatch(controller,
             ::google::protobuf::down_cast<const ::nlper::HttpRequest*>(request),
             ::google::protobuf::down_cast< ::nlper::HttpResponse*>(response),
             done);
      break;
    case 2:
      run_ddmatch(controller,
             ::google::protobuf::down_cast<const ::nlper::HttpRequest*>(request),
             ::google::protobuf::down_cast< ::nlper::HttpResponse*>(response),
             done);
      break;
    default:
      GOOGLE_LOG(FATAL) << "Bad method index; this should never happen.";
      break;
  }
}

const ::google::protobuf::Message& HttpService::GetRequestPrototype(
    const ::google::protobuf::MethodDescriptor* method) const {
  GOOGLE_DCHECK_EQ(method->service(), descriptor());
  switch(method->index()) {
    case 0:
      return ::nlper::HttpRequest::default_instance();
    case 1:
      return ::nlper::HttpRequest::default_instance();
    case 2:
      return ::nlper::HttpRequest::default_instance();
    default:
      GOOGLE_LOG(FATAL) << "Bad method index; this should never happen.";
      return *::google::protobuf::MessageFactory::generated_factory()
          ->GetPrototype(method->input_type());
  }
}

const ::google::protobuf::Message& HttpService::GetResponsePrototype(
    const ::google::protobuf::MethodDescriptor* method) const {
  GOOGLE_DCHECK_EQ(method->service(), descriptor());
  switch(method->index()) {
    case 0:
      return ::nlper::HttpResponse::default_instance();
    case 1:
      return ::nlper::HttpResponse::default_instance();
    case 2:
      return ::nlper::HttpResponse::default_instance();
    default:
      GOOGLE_LOG(FATAL) << "Bad method index; this should never happen.";
      return *::google::protobuf::MessageFactory::generated_factory()
          ->GetPrototype(method->output_type());
  }
}

HttpService_Stub::HttpService_Stub(::google::protobuf::RpcChannel* channel)
  : channel_(channel), owns_channel_(false) {}
HttpService_Stub::HttpService_Stub(
    ::google::protobuf::RpcChannel* channel,
    ::google::protobuf::Service::ChannelOwnership ownership)
  : channel_(channel),
    owns_channel_(ownership == ::google::protobuf::Service::STUB_OWNS_CHANNEL) {}
HttpService_Stub::~HttpService_Stub() {
  if (owns_channel_) delete channel_;
}

void HttpService_Stub::run_semtopic(::google::protobuf::RpcController* controller,
                              const ::nlper::HttpRequest* request,
                              ::nlper::HttpResponse* response,
                              ::google::protobuf::Closure* done) {
  channel_->CallMethod(descriptor()->method(0),
                       controller, request, response, done);
}
void HttpService_Stub::run_qdmatch(::google::protobuf::RpcController* controller,
                              const ::nlper::HttpRequest* request,
                              ::nlper::HttpResponse* response,
                              ::google::protobuf::Closure* done) {
  channel_->CallMethod(descriptor()->method(1),
                       controller, request, response, done);
}
void HttpService_Stub::run_ddmatch(::google::protobuf::RpcController* controller,
                              const ::nlper::HttpRequest* request,
                              ::nlper::HttpResponse* response,
                              ::google::protobuf::Closure* done) {
  channel_->CallMethod(descriptor()->method(2),
                       controller, request, response, done);
}

// @@protoc_insertion_point(namespace_scope)

}  // namespace nlper

// @@protoc_insertion_point(global_scope)