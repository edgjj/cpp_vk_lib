#ifndef VK_EVENTS_HANDLERS_MESSAGE_ACTION_HANDLER_HPP
#define VK_EVENTS_HANDLERS_MESSAGE_ACTION_HANDLER_HPP

#include <string>
#include <variant>

namespace vk::action {

struct chat_invite_user
{
    int64_t member_id;
};

struct chat_kick_user
{
    int64_t member_id;
};

struct chat_pin_message
{
    int64_t member_id;
    int64_t conversation_member_id;
    std::string message;
};

struct chat_unpin_message
{
    int64_t member_id;
    int64_t conversation_member_id;
};

struct chat_photo_update
{
    // Empty.
};

struct chat_title_update
{
    std::string text;
};

using any_action_t = std::variant<
    chat_invite_user,
    chat_kick_user,
    chat_pin_message,
    chat_unpin_message,
    chat_photo_update,
    chat_title_update
>;

}// namespace vk::action

#endif// VK_EVENTS_HANDLERS_MESSAGE_ACTION_HANDLER_HPP
