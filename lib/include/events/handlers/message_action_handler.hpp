#ifndef VK_EVENT_MESSAGE_ACTION_HANDLER_H
#define VK_EVENT_MESSAGE_ACTION_HANDLER_H

#include <string>
#include <memory>
#include <variant>


namespace vk {
namespace action {

struct chat_invite_user {
  std::int64_t member_id;
};

struct chat_kick_user {
  std::int64_t member_id;
};

struct chat_pin_message {
  std::int64_t member_id;
  std::int64_t conversation_member_id;
  std::string message;
};

struct chat_unpin_message {
  std::int64_t member_id;
  std::int64_t conversation_member_id;
};

struct chat_photo_update {
// Empty.
};

struct chat_title_update {
  std::string text;
};

using any_action = std::variant<
  chat_invite_user,
  chat_kick_user,
  chat_pin_message,
  chat_unpin_message,
  chat_photo_update,
  chat_title_update
>;

template <typename _Action>
inline _Action get(const any_action& action) noexcept {
  return std::get<_Action>(action);
}

} // namespace action
} // namespace vk

#endif // VK_EVENT_MESSAGE_ACTION_HANDLER_H
