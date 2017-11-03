// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: GameDefine.proto

#ifndef PROTOBUF_GameDefine_2eproto__INCLUDED
#define PROTOBUF_GameDefine_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3000000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3000000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_enum_util.h>
// @@protoc_insertion_point(includes)

namespace GameDefine {

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_GameDefine_2eproto();
void protobuf_AssignDesc_GameDefine_2eproto();
void protobuf_ShutdownFile_GameDefine_2eproto();


enum Capcity {
  BagLimit = 180,
  Bag = 50,
  ChildGroup = 5,
  Equip = 30,
  Store = 50,
  Mail = 100,
  Function = 160,
  ProertyCount = 100
};
bool Capcity_IsValid(int value);
const Capcity Capcity_MIN = ChildGroup;
const Capcity Capcity_MAX = BagLimit;
const int Capcity_ARRAYSIZE = Capcity_MAX + 1;

enum ItemDeleteReason {
  Invalid = 0,
  Client = 1,
  Move = 2,
  Combine = 3
};
bool ItemDeleteReason_IsValid(int value);
const ItemDeleteReason ItemDeleteReason_MIN = Invalid;
const ItemDeleteReason ItemDeleteReason_MAX = Combine;
const int ItemDeleteReason_ARRAYSIZE = ItemDeleteReason_MAX + 1;

enum ItemRefreshReason {
  ItemRefreshReason_None = 0
};
bool ItemRefreshReason_IsValid(int value);
const ItemRefreshReason ItemRefreshReason_MIN = ItemRefreshReason_None;
const ItemRefreshReason ItemRefreshReason_MAX = ItemRefreshReason_None;
const int ItemRefreshReason_ARRAYSIZE = ItemRefreshReason_MAX + 1;

enum ItemLocation {
  ItemLocation_None = 0,
  ItemLocation_Bag = 1,
  ItemLocation_Equip = 2
};
bool ItemLocation_IsValid(int value);
const ItemLocation ItemLocation_MIN = ItemLocation_None;
const ItemLocation ItemLocation_MAX = ItemLocation_Equip;
const int ItemLocation_ARRAYSIZE = ItemLocation_MAX + 1;

enum ItemSellSource {
  ItemSellSource_Invalid = 0
};
bool ItemSellSource_IsValid(int value);
const ItemSellSource ItemSellSource_MIN = ItemSellSource_Invalid;
const ItemSellSource ItemSellSource_MAX = ItemSellSource_Invalid;
const int ItemSellSource_ARRAYSIZE = ItemSellSource_MAX + 1;

// ===================================================================


// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace GameDefine

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::GameDefine::Capcity> : ::google::protobuf::internal::true_type {};
template <> struct is_proto_enum< ::GameDefine::ItemDeleteReason> : ::google::protobuf::internal::true_type {};
template <> struct is_proto_enum< ::GameDefine::ItemRefreshReason> : ::google::protobuf::internal::true_type {};
template <> struct is_proto_enum< ::GameDefine::ItemLocation> : ::google::protobuf::internal::true_type {};
template <> struct is_proto_enum< ::GameDefine::ItemSellSource> : ::google::protobuf::internal::true_type {};

}  // namespace protobuf
}  // namespace google
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_GameDefine_2eproto__INCLUDED
