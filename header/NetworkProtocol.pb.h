// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: NetworkProtocol.proto

#ifndef PROTOBUF_NetworkProtocol_2eproto__INCLUDED
#define PROTOBUF_NetworkProtocol_2eproto__INCLUDED

#include <string>

#include "protobuf/stubs/common.h"

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

#include "protobuf/generated_message_util.h"
#include "protobuf/message.h"
#include "protobuf/repeated_field.h"
#include "protobuf/extension_set.h"
#include "protobuf/generated_enum_reflection.h"
#include "protobuf/unknown_field_set.h"
// @@protoc_insertion_point(includes)

namespace Bomberman {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_NetworkProtocol_2eproto();
void protobuf_AssignDesc_NetworkProtocol_2eproto();
void protobuf_ShutdownFile_NetworkProtocol_2eproto();

class Message;
class Message_Player;
class Message_Map;
class Message_Info;
class Message_OwnPlayerInfo;

enum Message_Player_Dir {
  Message_Player_Dir_NORTH = 1,
  Message_Player_Dir_SOUTH = 2,
  Message_Player_Dir_EAST = 3,
  Message_Player_Dir_WEST = 4
};
bool Message_Player_Dir_IsValid(int value);
const Message_Player_Dir Message_Player_Dir_Dir_MIN = Message_Player_Dir_NORTH;
const Message_Player_Dir Message_Player_Dir_Dir_MAX = Message_Player_Dir_WEST;
const int Message_Player_Dir_Dir_ARRAYSIZE = Message_Player_Dir_Dir_MAX + 1;

const ::google::protobuf::EnumDescriptor* Message_Player_Dir_descriptor();
inline const ::std::string& Message_Player_Dir_Name(Message_Player_Dir value) {
  return ::google::protobuf::internal::NameOfEnum(
    Message_Player_Dir_descriptor(), value);
}
inline bool Message_Player_Dir_Parse(
    const ::std::string& name, Message_Player_Dir* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Message_Player_Dir>(
    Message_Player_Dir_descriptor(), name, value);
}
enum Message_MessageType {
  Message_MessageType_OWN_MOVE = 1,
  Message_MessageType_OWN_BOMB = 2,
  Message_MessageType_MAP_UPDATE = 3,
  Message_MessageType_PLAYER_UPDATE = 4,
  Message_MessageType_INFOS = 5,
  Message_MessageType_CONSUME_BONUS = 6,
  Message_MessageType_OWN_PLAYER_INFO = 7
};
bool Message_MessageType_IsValid(int value);
const Message_MessageType Message_MessageType_MessageType_MIN = Message_MessageType_OWN_MOVE;
const Message_MessageType Message_MessageType_MessageType_MAX = Message_MessageType_OWN_PLAYER_INFO;
const int Message_MessageType_MessageType_ARRAYSIZE = Message_MessageType_MessageType_MAX + 1;

const ::google::protobuf::EnumDescriptor* Message_MessageType_descriptor();
inline const ::std::string& Message_MessageType_Name(Message_MessageType value) {
  return ::google::protobuf::internal::NameOfEnum(
    Message_MessageType_descriptor(), value);
}
inline bool Message_MessageType_Parse(
    const ::std::string& name, Message_MessageType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Message_MessageType>(
    Message_MessageType_descriptor(), name, value);
}
// ===================================================================

class Message_Player : public ::google::protobuf::Message {
 public:
  Message_Player();
  virtual ~Message_Player();

  Message_Player(const Message_Player& from);

  inline Message_Player& operator=(const Message_Player& from) {
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
  static const Message_Player& default_instance();

  void Swap(Message_Player* other);

  // implements Message ----------------------------------------------

  Message_Player* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Message_Player& from);
  void MergeFrom(const Message_Player& from);
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

  typedef Message_Player_Dir Dir;
  static const Dir NORTH = Message_Player_Dir_NORTH;
  static const Dir SOUTH = Message_Player_Dir_SOUTH;
  static const Dir EAST = Message_Player_Dir_EAST;
  static const Dir WEST = Message_Player_Dir_WEST;
  static inline bool Dir_IsValid(int value) {
    return Message_Player_Dir_IsValid(value);
  }
  static const Dir Dir_MIN =
    Message_Player_Dir_Dir_MIN;
  static const Dir Dir_MAX =
    Message_Player_Dir_Dir_MAX;
  static const int Dir_ARRAYSIZE =
    Message_Player_Dir_Dir_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  Dir_descriptor() {
    return Message_Player_Dir_descriptor();
  }
  static inline const ::std::string& Dir_Name(Dir value) {
    return Message_Player_Dir_Name(value);
  }
  static inline bool Dir_Parse(const ::std::string& name,
      Dir* value) {
    return Message_Player_Dir_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // required int32 playerId = 1;
  inline bool has_playerid() const;
  inline void clear_playerid();
  static const int kPlayerIdFieldNumber = 1;
  inline ::google::protobuf::int32 playerid() const;
  inline void set_playerid(::google::protobuf::int32 value);

  // required float x = 2;
  inline bool has_x() const;
  inline void clear_x();
  static const int kXFieldNumber = 2;
  inline float x() const;
  inline void set_x(float value);

  // required float y = 3;
  inline bool has_y() const;
  inline void clear_y();
  static const int kYFieldNumber = 3;
  inline float y() const;
  inline void set_y(float value);

  // required .Bomberman.Message.Player.Dir dir = 4;
  inline bool has_dir() const;
  inline void clear_dir();
  static const int kDirFieldNumber = 4;
  inline ::Bomberman::Message_Player_Dir dir() const;
  inline void set_dir(::Bomberman::Message_Player_Dir value);

  // @@protoc_insertion_point(class_scope:Bomberman.Message.Player)
 private:
  inline void set_has_playerid();
  inline void clear_has_playerid();
  inline void set_has_x();
  inline void clear_has_x();
  inline void set_has_y();
  inline void clear_has_y();
  inline void set_has_dir();
  inline void clear_has_dir();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::int32 playerid_;
  float x_;
  float y_;
  int dir_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(4 + 31) / 32];

  friend void  protobuf_AddDesc_NetworkProtocol_2eproto();
  friend void protobuf_AssignDesc_NetworkProtocol_2eproto();
  friend void protobuf_ShutdownFile_NetworkProtocol_2eproto();

  void InitAsDefaultInstance();
  static Message_Player* default_instance_;
};
// -------------------------------------------------------------------

class Message_Map : public ::google::protobuf::Message {
 public:
  Message_Map();
  virtual ~Message_Map();

  Message_Map(const Message_Map& from);

  inline Message_Map& operator=(const Message_Map& from) {
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
  static const Message_Map& default_instance();

  void Swap(Message_Map* other);

  // implements Message ----------------------------------------------

  Message_Map* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Message_Map& from);
  void MergeFrom(const Message_Map& from);
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

  // required int32 startX = 1;
  inline bool has_startx() const;
  inline void clear_startx();
  static const int kStartXFieldNumber = 1;
  inline ::google::protobuf::int32 startx() const;
  inline void set_startx(::google::protobuf::int32 value);

  // required int32 startY = 2;
  inline bool has_starty() const;
  inline void clear_starty();
  static const int kStartYFieldNumber = 2;
  inline ::google::protobuf::int32 starty() const;
  inline void set_starty(::google::protobuf::int32 value);

  // required bytes data = 3;
  inline bool has_data() const;
  inline void clear_data();
  static const int kDataFieldNumber = 3;
  inline const ::std::string& data() const;
  inline void set_data(const ::std::string& value);
  inline void set_data(const char* value);
  inline void set_data(const void* value, size_t size);
  inline ::std::string* mutable_data();
  inline ::std::string* release_data();
  inline void set_allocated_data(::std::string* data);

  // @@protoc_insertion_point(class_scope:Bomberman.Message.Map)
 private:
  inline void set_has_startx();
  inline void clear_has_startx();
  inline void set_has_starty();
  inline void clear_has_starty();
  inline void set_has_data();
  inline void clear_has_data();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::int32 startx_;
  ::google::protobuf::int32 starty_;
  ::std::string* data_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];

  friend void  protobuf_AddDesc_NetworkProtocol_2eproto();
  friend void protobuf_AssignDesc_NetworkProtocol_2eproto();
  friend void protobuf_ShutdownFile_NetworkProtocol_2eproto();

  void InitAsDefaultInstance();
  static Message_Map* default_instance_;
};
// -------------------------------------------------------------------

class Message_Info : public ::google::protobuf::Message {
 public:
  Message_Info();
  virtual ~Message_Info();

  Message_Info(const Message_Info& from);

  inline Message_Info& operator=(const Message_Info& from) {
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
  static const Message_Info& default_instance();

  void Swap(Message_Info* other);

  // implements Message ----------------------------------------------

  Message_Info* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Message_Info& from);
  void MergeFrom(const Message_Info& from);
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

  // required int32 mapSize = 1;
  inline bool has_mapsize() const;
  inline void clear_mapsize();
  static const int kMapSizeFieldNumber = 1;
  inline ::google::protobuf::int32 mapsize() const;
  inline void set_mapsize(::google::protobuf::int32 value);

  // required int32 playersNb = 2;
  inline bool has_playersnb() const;
  inline void clear_playersnb();
  static const int kPlayersNbFieldNumber = 2;
  inline ::google::protobuf::int32 playersnb() const;
  inline void set_playersnb(::google::protobuf::int32 value);

  // required float startX = 3;
  inline bool has_startx() const;
  inline void clear_startx();
  static const int kStartXFieldNumber = 3;
  inline float startx() const;
  inline void set_startx(float value);

  // required float startY = 4;
  inline bool has_starty() const;
  inline void clear_starty();
  static const int kStartYFieldNumber = 4;
  inline float starty() const;
  inline void set_starty(float value);

  // @@protoc_insertion_point(class_scope:Bomberman.Message.Info)
 private:
  inline void set_has_mapsize();
  inline void clear_has_mapsize();
  inline void set_has_playersnb();
  inline void clear_has_playersnb();
  inline void set_has_startx();
  inline void clear_has_startx();
  inline void set_has_starty();
  inline void clear_has_starty();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::int32 mapsize_;
  ::google::protobuf::int32 playersnb_;
  float startx_;
  float starty_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(4 + 31) / 32];

  friend void  protobuf_AddDesc_NetworkProtocol_2eproto();
  friend void protobuf_AssignDesc_NetworkProtocol_2eproto();
  friend void protobuf_ShutdownFile_NetworkProtocol_2eproto();

  void InitAsDefaultInstance();
  static Message_Info* default_instance_;
};
// -------------------------------------------------------------------

class Message_OwnPlayerInfo : public ::google::protobuf::Message {
 public:
  Message_OwnPlayerInfo();
  virtual ~Message_OwnPlayerInfo();

  Message_OwnPlayerInfo(const Message_OwnPlayerInfo& from);

  inline Message_OwnPlayerInfo& operator=(const Message_OwnPlayerInfo& from) {
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
  static const Message_OwnPlayerInfo& default_instance();

  void Swap(Message_OwnPlayerInfo* other);

  // implements Message ----------------------------------------------

  Message_OwnPlayerInfo* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Message_OwnPlayerInfo& from);
  void MergeFrom(const Message_OwnPlayerInfo& from);
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

  // required int32 life = 1;
  inline bool has_life() const;
  inline void clear_life();
  static const int kLifeFieldNumber = 1;
  inline ::google::protobuf::int32 life() const;
  inline void set_life(::google::protobuf::int32 value);

  // required int32 range = 2;
  inline bool has_range() const;
  inline void clear_range();
  static const int kRangeFieldNumber = 2;
  inline ::google::protobuf::int32 range() const;
  inline void set_range(::google::protobuf::int32 value);

  // required int32 stock = 3;
  inline bool has_stock() const;
  inline void clear_stock();
  static const int kStockFieldNumber = 3;
  inline ::google::protobuf::int32 stock() const;
  inline void set_stock(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:Bomberman.Message.OwnPlayerInfo)
 private:
  inline void set_has_life();
  inline void clear_has_life();
  inline void set_has_range();
  inline void clear_has_range();
  inline void set_has_stock();
  inline void clear_has_stock();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::int32 life_;
  ::google::protobuf::int32 range_;
  ::google::protobuf::int32 stock_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];

  friend void  protobuf_AddDesc_NetworkProtocol_2eproto();
  friend void protobuf_AssignDesc_NetworkProtocol_2eproto();
  friend void protobuf_ShutdownFile_NetworkProtocol_2eproto();

  void InitAsDefaultInstance();
  static Message_OwnPlayerInfo* default_instance_;
};
// -------------------------------------------------------------------

class Message : public ::google::protobuf::Message {
 public:
  Message();
  virtual ~Message();

  Message(const Message& from);

  inline Message& operator=(const Message& from) {
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
  static const Message& default_instance();

  void Swap(Message* other);

  // implements Message ----------------------------------------------

  Message* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Message& from);
  void MergeFrom(const Message& from);
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

  typedef Message_Player Player;
  typedef Message_Map Map;
  typedef Message_Info Info;
  typedef Message_OwnPlayerInfo OwnPlayerInfo;

  typedef Message_MessageType MessageType;
  static const MessageType OWN_MOVE = Message_MessageType_OWN_MOVE;
  static const MessageType OWN_BOMB = Message_MessageType_OWN_BOMB;
  static const MessageType MAP_UPDATE = Message_MessageType_MAP_UPDATE;
  static const MessageType PLAYER_UPDATE = Message_MessageType_PLAYER_UPDATE;
  static const MessageType INFOS = Message_MessageType_INFOS;
  static const MessageType CONSUME_BONUS = Message_MessageType_CONSUME_BONUS;
  static const MessageType OWN_PLAYER_INFO = Message_MessageType_OWN_PLAYER_INFO;
  static inline bool MessageType_IsValid(int value) {
    return Message_MessageType_IsValid(value);
  }
  static const MessageType MessageType_MIN =
    Message_MessageType_MessageType_MIN;
  static const MessageType MessageType_MAX =
    Message_MessageType_MessageType_MAX;
  static const int MessageType_ARRAYSIZE =
    Message_MessageType_MessageType_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  MessageType_descriptor() {
    return Message_MessageType_descriptor();
  }
  static inline const ::std::string& MessageType_Name(MessageType value) {
    return Message_MessageType_Name(value);
  }
  static inline bool MessageType_Parse(const ::std::string& name,
      MessageType* value) {
    return Message_MessageType_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // required .Bomberman.Message.MessageType type = 1;
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 1;
  inline ::Bomberman::Message_MessageType type() const;
  inline void set_type(::Bomberman::Message_MessageType value);

  // repeated .Bomberman.Message.Player player = 4;
  inline int player_size() const;
  inline void clear_player();
  static const int kPlayerFieldNumber = 4;
  inline const ::Bomberman::Message_Player& player(int index) const;
  inline ::Bomberman::Message_Player* mutable_player(int index);
  inline ::Bomberman::Message_Player* add_player();
  inline const ::google::protobuf::RepeatedPtrField< ::Bomberman::Message_Player >&
      player() const;
  inline ::google::protobuf::RepeatedPtrField< ::Bomberman::Message_Player >*
      mutable_player();

  // repeated .Bomberman.Message.Map map = 5;
  inline int map_size() const;
  inline void clear_map();
  static const int kMapFieldNumber = 5;
  inline const ::Bomberman::Message_Map& map(int index) const;
  inline ::Bomberman::Message_Map* mutable_map(int index);
  inline ::Bomberman::Message_Map* add_map();
  inline const ::google::protobuf::RepeatedPtrField< ::Bomberman::Message_Map >&
      map() const;
  inline ::google::protobuf::RepeatedPtrField< ::Bomberman::Message_Map >*
      mutable_map();

  // repeated .Bomberman.Message.Info info = 6;
  inline int info_size() const;
  inline void clear_info();
  static const int kInfoFieldNumber = 6;
  inline const ::Bomberman::Message_Info& info(int index) const;
  inline ::Bomberman::Message_Info* mutable_info(int index);
  inline ::Bomberman::Message_Info* add_info();
  inline const ::google::protobuf::RepeatedPtrField< ::Bomberman::Message_Info >&
      info() const;
  inline ::google::protobuf::RepeatedPtrField< ::Bomberman::Message_Info >*
      mutable_info();

  // repeated .Bomberman.Message.OwnPlayerInfo ownPlayerInfo = 7;
  inline int ownplayerinfo_size() const;
  inline void clear_ownplayerinfo();
  static const int kOwnPlayerInfoFieldNumber = 7;
  inline const ::Bomberman::Message_OwnPlayerInfo& ownplayerinfo(int index) const;
  inline ::Bomberman::Message_OwnPlayerInfo* mutable_ownplayerinfo(int index);
  inline ::Bomberman::Message_OwnPlayerInfo* add_ownplayerinfo();
  inline const ::google::protobuf::RepeatedPtrField< ::Bomberman::Message_OwnPlayerInfo >&
      ownplayerinfo() const;
  inline ::google::protobuf::RepeatedPtrField< ::Bomberman::Message_OwnPlayerInfo >*
      mutable_ownplayerinfo();

  // @@protoc_insertion_point(class_scope:Bomberman.Message)
 private:
  inline void set_has_type();
  inline void clear_has_type();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedPtrField< ::Bomberman::Message_Player > player_;
  ::google::protobuf::RepeatedPtrField< ::Bomberman::Message_Map > map_;
  ::google::protobuf::RepeatedPtrField< ::Bomberman::Message_Info > info_;
  ::google::protobuf::RepeatedPtrField< ::Bomberman::Message_OwnPlayerInfo > ownplayerinfo_;
  int type_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(5 + 31) / 32];

  friend void  protobuf_AddDesc_NetworkProtocol_2eproto();
  friend void protobuf_AssignDesc_NetworkProtocol_2eproto();
  friend void protobuf_ShutdownFile_NetworkProtocol_2eproto();

  void InitAsDefaultInstance();
  static Message* default_instance_;
};
// ===================================================================


// ===================================================================

// Message_Player

// required int32 playerId = 1;
inline bool Message_Player::has_playerid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Message_Player::set_has_playerid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Message_Player::clear_has_playerid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Message_Player::clear_playerid() {
  playerid_ = 0;
  clear_has_playerid();
}
inline ::google::protobuf::int32 Message_Player::playerid() const {
  return playerid_;
}
inline void Message_Player::set_playerid(::google::protobuf::int32 value) {
  set_has_playerid();
  playerid_ = value;
}

// required float x = 2;
inline bool Message_Player::has_x() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Message_Player::set_has_x() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Message_Player::clear_has_x() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Message_Player::clear_x() {
  x_ = 0;
  clear_has_x();
}
inline float Message_Player::x() const {
  return x_;
}
inline void Message_Player::set_x(float value) {
  set_has_x();
  x_ = value;
}

// required float y = 3;
inline bool Message_Player::has_y() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Message_Player::set_has_y() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Message_Player::clear_has_y() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Message_Player::clear_y() {
  y_ = 0;
  clear_has_y();
}
inline float Message_Player::y() const {
  return y_;
}
inline void Message_Player::set_y(float value) {
  set_has_y();
  y_ = value;
}

// required .Bomberman.Message.Player.Dir dir = 4;
inline bool Message_Player::has_dir() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void Message_Player::set_has_dir() {
  _has_bits_[0] |= 0x00000008u;
}
inline void Message_Player::clear_has_dir() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void Message_Player::clear_dir() {
  dir_ = 1;
  clear_has_dir();
}
inline ::Bomberman::Message_Player_Dir Message_Player::dir() const {
  return static_cast< ::Bomberman::Message_Player_Dir >(dir_);
}
inline void Message_Player::set_dir(::Bomberman::Message_Player_Dir value) {
  assert(::Bomberman::Message_Player_Dir_IsValid(value));
  set_has_dir();
  dir_ = value;
}

// -------------------------------------------------------------------

// Message_Map

// required int32 startX = 1;
inline bool Message_Map::has_startx() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Message_Map::set_has_startx() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Message_Map::clear_has_startx() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Message_Map::clear_startx() {
  startx_ = 0;
  clear_has_startx();
}
inline ::google::protobuf::int32 Message_Map::startx() const {
  return startx_;
}
inline void Message_Map::set_startx(::google::protobuf::int32 value) {
  set_has_startx();
  startx_ = value;
}

// required int32 startY = 2;
inline bool Message_Map::has_starty() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Message_Map::set_has_starty() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Message_Map::clear_has_starty() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Message_Map::clear_starty() {
  starty_ = 0;
  clear_has_starty();
}
inline ::google::protobuf::int32 Message_Map::starty() const {
  return starty_;
}
inline void Message_Map::set_starty(::google::protobuf::int32 value) {
  set_has_starty();
  starty_ = value;
}

// required bytes data = 3;
inline bool Message_Map::has_data() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Message_Map::set_has_data() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Message_Map::clear_has_data() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Message_Map::clear_data() {
  if (data_ != &::google::protobuf::internal::kEmptyString) {
    data_->clear();
  }
  clear_has_data();
}
inline const ::std::string& Message_Map::data() const {
  return *data_;
}
inline void Message_Map::set_data(const ::std::string& value) {
  set_has_data();
  if (data_ == &::google::protobuf::internal::kEmptyString) {
    data_ = new ::std::string;
  }
  data_->assign(value);
}
inline void Message_Map::set_data(const char* value) {
  set_has_data();
  if (data_ == &::google::protobuf::internal::kEmptyString) {
    data_ = new ::std::string;
  }
  data_->assign(value);
}
inline void Message_Map::set_data(const void* value, size_t size) {
  set_has_data();
  if (data_ == &::google::protobuf::internal::kEmptyString) {
    data_ = new ::std::string;
  }
  data_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Message_Map::mutable_data() {
  set_has_data();
  if (data_ == &::google::protobuf::internal::kEmptyString) {
    data_ = new ::std::string;
  }
  return data_;
}
inline ::std::string* Message_Map::release_data() {
  clear_has_data();
  if (data_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = data_;
    data_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void Message_Map::set_allocated_data(::std::string* data) {
  if (data_ != &::google::protobuf::internal::kEmptyString) {
    delete data_;
  }
  if (data) {
    set_has_data();
    data_ = data;
  } else {
    clear_has_data();
    data_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// -------------------------------------------------------------------

// Message_Info

// required int32 mapSize = 1;
inline bool Message_Info::has_mapsize() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Message_Info::set_has_mapsize() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Message_Info::clear_has_mapsize() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Message_Info::clear_mapsize() {
  mapsize_ = 0;
  clear_has_mapsize();
}
inline ::google::protobuf::int32 Message_Info::mapsize() const {
  return mapsize_;
}
inline void Message_Info::set_mapsize(::google::protobuf::int32 value) {
  set_has_mapsize();
  mapsize_ = value;
}

// required int32 playersNb = 2;
inline bool Message_Info::has_playersnb() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Message_Info::set_has_playersnb() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Message_Info::clear_has_playersnb() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Message_Info::clear_playersnb() {
  playersnb_ = 0;
  clear_has_playersnb();
}
inline ::google::protobuf::int32 Message_Info::playersnb() const {
  return playersnb_;
}
inline void Message_Info::set_playersnb(::google::protobuf::int32 value) {
  set_has_playersnb();
  playersnb_ = value;
}

// required float startX = 3;
inline bool Message_Info::has_startx() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Message_Info::set_has_startx() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Message_Info::clear_has_startx() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Message_Info::clear_startx() {
  startx_ = 0;
  clear_has_startx();
}
inline float Message_Info::startx() const {
  return startx_;
}
inline void Message_Info::set_startx(float value) {
  set_has_startx();
  startx_ = value;
}

// required float startY = 4;
inline bool Message_Info::has_starty() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void Message_Info::set_has_starty() {
  _has_bits_[0] |= 0x00000008u;
}
inline void Message_Info::clear_has_starty() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void Message_Info::clear_starty() {
  starty_ = 0;
  clear_has_starty();
}
inline float Message_Info::starty() const {
  return starty_;
}
inline void Message_Info::set_starty(float value) {
  set_has_starty();
  starty_ = value;
}

// -------------------------------------------------------------------

// Message_OwnPlayerInfo

// required int32 life = 1;
inline bool Message_OwnPlayerInfo::has_life() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Message_OwnPlayerInfo::set_has_life() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Message_OwnPlayerInfo::clear_has_life() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Message_OwnPlayerInfo::clear_life() {
  life_ = 0;
  clear_has_life();
}
inline ::google::protobuf::int32 Message_OwnPlayerInfo::life() const {
  return life_;
}
inline void Message_OwnPlayerInfo::set_life(::google::protobuf::int32 value) {
  set_has_life();
  life_ = value;
}

// required int32 range = 2;
inline bool Message_OwnPlayerInfo::has_range() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Message_OwnPlayerInfo::set_has_range() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Message_OwnPlayerInfo::clear_has_range() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Message_OwnPlayerInfo::clear_range() {
  range_ = 0;
  clear_has_range();
}
inline ::google::protobuf::int32 Message_OwnPlayerInfo::range() const {
  return range_;
}
inline void Message_OwnPlayerInfo::set_range(::google::protobuf::int32 value) {
  set_has_range();
  range_ = value;
}

// required int32 stock = 3;
inline bool Message_OwnPlayerInfo::has_stock() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Message_OwnPlayerInfo::set_has_stock() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Message_OwnPlayerInfo::clear_has_stock() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Message_OwnPlayerInfo::clear_stock() {
  stock_ = 0;
  clear_has_stock();
}
inline ::google::protobuf::int32 Message_OwnPlayerInfo::stock() const {
  return stock_;
}
inline void Message_OwnPlayerInfo::set_stock(::google::protobuf::int32 value) {
  set_has_stock();
  stock_ = value;
}

// -------------------------------------------------------------------

// Message

// required .Bomberman.Message.MessageType type = 1;
inline bool Message::has_type() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Message::set_has_type() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Message::clear_has_type() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Message::clear_type() {
  type_ = 1;
  clear_has_type();
}
inline ::Bomberman::Message_MessageType Message::type() const {
  return static_cast< ::Bomberman::Message_MessageType >(type_);
}
inline void Message::set_type(::Bomberman::Message_MessageType value) {
  assert(::Bomberman::Message_MessageType_IsValid(value));
  set_has_type();
  type_ = value;
}

// repeated .Bomberman.Message.Player player = 4;
inline int Message::player_size() const {
  return player_.size();
}
inline void Message::clear_player() {
  player_.Clear();
}
inline const ::Bomberman::Message_Player& Message::player(int index) const {
  return player_.Get(index);
}
inline ::Bomberman::Message_Player* Message::mutable_player(int index) {
  return player_.Mutable(index);
}
inline ::Bomberman::Message_Player* Message::add_player() {
  return player_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::Bomberman::Message_Player >&
Message::player() const {
  return player_;
}
inline ::google::protobuf::RepeatedPtrField< ::Bomberman::Message_Player >*
Message::mutable_player() {
  return &player_;
}

// repeated .Bomberman.Message.Map map = 5;
inline int Message::map_size() const {
  return map_.size();
}
inline void Message::clear_map() {
  map_.Clear();
}
inline const ::Bomberman::Message_Map& Message::map(int index) const {
  return map_.Get(index);
}
inline ::Bomberman::Message_Map* Message::mutable_map(int index) {
  return map_.Mutable(index);
}
inline ::Bomberman::Message_Map* Message::add_map() {
  return map_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::Bomberman::Message_Map >&
Message::map() const {
  return map_;
}
inline ::google::protobuf::RepeatedPtrField< ::Bomberman::Message_Map >*
Message::mutable_map() {
  return &map_;
}

// repeated .Bomberman.Message.Info info = 6;
inline int Message::info_size() const {
  return info_.size();
}
inline void Message::clear_info() {
  info_.Clear();
}
inline const ::Bomberman::Message_Info& Message::info(int index) const {
  return info_.Get(index);
}
inline ::Bomberman::Message_Info* Message::mutable_info(int index) {
  return info_.Mutable(index);
}
inline ::Bomberman::Message_Info* Message::add_info() {
  return info_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::Bomberman::Message_Info >&
Message::info() const {
  return info_;
}
inline ::google::protobuf::RepeatedPtrField< ::Bomberman::Message_Info >*
Message::mutable_info() {
  return &info_;
}

// repeated .Bomberman.Message.OwnPlayerInfo ownPlayerInfo = 7;
inline int Message::ownplayerinfo_size() const {
  return ownplayerinfo_.size();
}
inline void Message::clear_ownplayerinfo() {
  ownplayerinfo_.Clear();
}
inline const ::Bomberman::Message_OwnPlayerInfo& Message::ownplayerinfo(int index) const {
  return ownplayerinfo_.Get(index);
}
inline ::Bomberman::Message_OwnPlayerInfo* Message::mutable_ownplayerinfo(int index) {
  return ownplayerinfo_.Mutable(index);
}
inline ::Bomberman::Message_OwnPlayerInfo* Message::add_ownplayerinfo() {
  return ownplayerinfo_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::Bomberman::Message_OwnPlayerInfo >&
Message::ownplayerinfo() const {
  return ownplayerinfo_;
}
inline ::google::protobuf::RepeatedPtrField< ::Bomberman::Message_OwnPlayerInfo >*
Message::mutable_ownplayerinfo() {
  return &ownplayerinfo_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace Bomberman

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::Bomberman::Message_Player_Dir>() {
  return ::Bomberman::Message_Player_Dir_descriptor();
}
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::Bomberman::Message_MessageType>() {
  return ::Bomberman::Message_MessageType_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_NetworkProtocol_2eproto__INCLUDED