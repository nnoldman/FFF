// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: GameDefine.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "GameDefine.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
// @@protoc_insertion_point(includes)

namespace GameDefine {

void protobuf_ShutdownFile_GameDefine_2eproto() {
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
void protobuf_AddDesc_GameDefine_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#else
void protobuf_AddDesc_GameDefine_2eproto() GOOGLE_ATTRIBUTE_COLD;
void protobuf_AddDesc_GameDefine_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#endif
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_GameDefine_2eproto);
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AddDesc_GameDefine_2eproto_once_);
void protobuf_AddDesc_GameDefine_2eproto() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AddDesc_GameDefine_2eproto_once_,
                 &protobuf_AddDesc_GameDefine_2eproto_impl);
}
#else
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_GameDefine_2eproto {
  StaticDescriptorInitializer_GameDefine_2eproto() {
    protobuf_AddDesc_GameDefine_2eproto();
  }
} static_descriptor_initializer_GameDefine_2eproto_;
#endif
bool Capcity_IsValid(int value) {
  switch(value) {
    case 5:
    case 30:
    case 50:
    case 100:
    case 160:
    case 180:
      return true;
    default:
      return false;
  }
}

bool ItemDeleteReason_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
    case 2:
    case 3:
      return true;
    default:
      return false;
  }
}

bool ItemRefreshReason_IsValid(int value) {
  switch(value) {
    case 0:
      return true;
    default:
      return false;
  }
}

bool ItemLocation_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
    case 2:
      return true;
    default:
      return false;
  }
}

bool ItemSellSource_IsValid(int value) {
  switch(value) {
    case 0:
      return true;
    default:
      return false;
  }
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace GameDefine

// @@protoc_insertion_point(global_scope)
