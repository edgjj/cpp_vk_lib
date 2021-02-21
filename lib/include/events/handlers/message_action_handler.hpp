#ifndef VK_MESSAGE_ACTION_HANDLER_H
#define VK_MESSAGE_ACTION_HANDLER_H

#include <string>
#include <memory>
#include <variant>

#include "misc/cppdefs.hpp"


namespace vk {
namespace action {

class vk_export chat_invite_user {
public:
  explicit chat_invite_user(std::int64_t member_id)
    : _member_id(member_id)
  { }
  std::int64_t member_id() const noexcept { return _member_id; }

private:
  std::int64_t _member_id;
};

class vk_export chat_kick_user {
public:
  explicit chat_kick_user(std::int64_t member_id)
    : _member_id(member_id)
  { }
  std::int64_t member_id() const noexcept { return _member_id; }

private:
  std::int64_t _member_id;
};

class vk_export chat_pin_message {
public:
  explicit chat_pin_message(std::int64_t member_id, std::int64_t conversation_member_id, std::string_view message)
    : _member_id(member_id), _conversation_member_id(conversation_member_id), _message(message)
  { }
  std::int64_t member_id() const noexcept { return _member_id; }
  std::int64_t conversation_member_id() const noexcept { return _conversation_member_id; }
  std::string message() const noexcept { return _message; }

private:
  std::int64_t _member_id;
  std::int64_t _conversation_member_id;
  std::string _message;
};

class vk_export chat_unpin_message {
public:
  explicit chat_unpin_message(std::int64_t member_id, std::int64_t conversation_member_id)
    : _member_id(member_id), _conversation_member_id(conversation_member_id)
  { }
  std::int64_t member_id() const noexcept { return _member_id; }
  std::int64_t conversation_member_id() const noexcept { return _conversation_member_id; }

private:
  std::int64_t _member_id;
  std::int64_t _conversation_member_id;
};

class vk_export chat_photo_update {
public:
  explicit chat_photo_update() = default;
};

class vk_export chat_title_update {
public:
  explicit chat_title_update(std::string_view text)
    : _text(text)
  { }
  std::string text() const noexcept { return _text; }

private:
  std::string _text;
};

using chat_invite_user_ptr = std::shared_ptr<chat_invite_user>;
using chat_kick_user_ptr = std::shared_ptr<chat_kick_user>;
using chat_pin_message_ptr = std::shared_ptr<chat_pin_message>;
using chat_unpin_message_ptr = std::shared_ptr<chat_unpin_message>;
using chat_photo_update_ptr = std::shared_ptr<chat_photo_update>;
using chat_title_update_ptr = std::shared_ptr<chat_title_update>;

using any_action = std::variant<
  chat_invite_user_ptr,
  chat_kick_user_ptr,
  chat_photo_update_ptr,
  chat_pin_message_ptr,
  chat_title_update_ptr,
  chat_unpin_message_ptr
>;

inline chat_invite_user_ptr get_chat_invite_user_action(const any_action& action) {
  return std::get<chat_invite_user_ptr>(action);
}
inline chat_kick_user_ptr chat_kick_user_action(const any_action& action) {
  return std::get<chat_kick_user_ptr>(action);
}
inline chat_photo_update_ptr get_chat_photo_update_action(const any_action& action) {
  return std::get<chat_photo_update_ptr>(action);
}
inline chat_pin_message_ptr get_chat_pin_message_action(const any_action& action) {
  return std::get<chat_pin_message_ptr>(action);
}
inline chat_title_update_ptr get_chat_title_update_action(const any_action& action) {
  return std::get<chat_title_update_ptr>(action);
}
inline chat_unpin_message_ptr get_chat_unpin_message_action(const any_action& action) {
  return std::get<chat_unpin_message_ptr>(action);
}
} // namespace action
} // namespace vk

#endif // VK_MESSAGE_ACTION_HANDLER_H
