#ifndef VK_MESSAGE_NEW_H
#define VK_MESSAGE_NEW_H

#include <variant>

#include "events/handlers/attachment_handler.hpp"
#include "events/handlers/message_action_handler.hpp"
#include "attachment/attachment.hpp"


namespace simdjson::dom {
class object;
class array;
} // namespace simdjson::dom

namespace vk {
namespace event {
class vk_export message_new {
public:
    message_new(std::string_view raw_json);
    message_new(
        std::int64_t peer_id, std::int64_t from_id,
        std::string_view text, std::string_view raw_json,
        const simdjson::dom::array& attachments
    );

    message_new reply() const;
    std::vector<std::shared_ptr<message_new>> fwd_messages() const;

    using any_action = std::variant<
        action::action_chat_invite_user_ptr,
        action::action_chat_kick_user_ptr,
        action::action_chat_photo_update_ptr,
        action::action_chat_pin_message_ptr,
        action::action_chat_title_update_ptr,
        action::action_chat_unpin_message_ptr
    >;

    std::string text()      const noexcept;
    std::string dump()      const noexcept;
    std::int64_t from_id()  const noexcept;
    std::int64_t peer_id()  const noexcept;
    bool has_reply()        const noexcept;
    bool has_fwd_messages() const noexcept;
    bool has_action()       const noexcept;
    any_action action()     const;
    attachment::attachments_t attachments() const;

private:
    void try_get_reply          (const simdjson::dom::object& object);
    void try_get_fwd_messages   (const simdjson::dom::array& messages);
    void try_get_actions        (const simdjson::dom::object& action);

    std::int64_t _peer_id;
    std::int64_t _from_id;
    std::string _text;
    std::string _raw_json;
    std::shared_ptr<message_new> _reply;
    any_action _action;
    std::vector<std::shared_ptr<message_new>> _fwd_messages;
    attachment::attachments_t _attachments;
    bool _has_action = false;
    bool _has_reply = false;
    bool _has_fwd_messages = false;

    attachment_handler att_handler;
};
} // namespace event
} // namespace vk

#endif // VK_MESSAGE_NEW_H
