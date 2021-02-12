#ifndef VK_MESSAGE_ACTION_HANDLER_H
#define VK_MESSAGE_ACTION_HANDLER_H

#include <string>
#include <memory>

#include "misc/cppdefs.hpp"

namespace vk {
namespace action {
class vk_export action_chat_invite_user {
public:
    explicit action_chat_invite_user(std::int64_t member_id)
        : _member_id(member_id)
    { }
    std::int64_t member_id() const noexcept { return _member_id; }

private:
    std::int64_t _member_id;
};

class vk_export action_chat_kick_user {
public:
    explicit action_chat_kick_user(std::int64_t member_id)
        : _member_id(member_id)
    { }
    std::int64_t member_id() const noexcept { return _member_id; }

private:
    std::int64_t _member_id;
};

class vk_export action_chat_pin_message {
public:
    explicit action_chat_pin_message(std::int64_t member_id, std::int64_t conversation_member_id, std::string_view message)
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

class vk_export action_chat_unpin_message {
public:
    explicit action_chat_unpin_message(std::int64_t member_id, std::int64_t conversation_member_id)
        : _member_id(member_id), _conversation_member_id(conversation_member_id)
    { }
    std::int64_t member_id() const noexcept { return _member_id; }
    std::int64_t conversation_member_id() const noexcept { return _conversation_member_id; }

private:
    std::int64_t _member_id;
    std::int64_t _conversation_member_id;
};

class vk_export action_chat_photo_update {
public:
    explicit action_chat_photo_update() { }
};

class vk_export action_chat_title_update {
public:
    explicit action_chat_title_update(std::string_view text)
        : _text(text)
    { }
    std::string text() const noexcept { return _text; }

private:
    std::string _text;
};

using action_chat_invite_user_ptr = std::shared_ptr<action_chat_invite_user>;
using action_chat_kick_user_ptr = std::shared_ptr<action_chat_kick_user>;
using action_chat_pin_message_ptr = std::shared_ptr<action_chat_pin_message>;
using action_chat_unpin_message_ptr = std::shared_ptr<action_chat_unpin_message>;
using action_chat_photo_update_ptr = std::shared_ptr<action_chat_photo_update>;
using action_chat_title_update_ptr = std::shared_ptr<action_chat_title_update>;
} // namespace action
} // namespace vk

#endif // VK_MESSAGE_ACTION_HANDLER_H
