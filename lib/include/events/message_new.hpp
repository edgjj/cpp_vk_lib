#ifndef VK_MESSAGE_NEW_H
#define VK_MESSAGE_NEW_H

#include "events/handlers/attachment_handler.hpp"
#include "events/handlers/message_action_handler.hpp"
#include "attachment/attachment.hpp"


namespace simdjson {
namespace dom {
class object;
class array;
} // namespace dom
} // namespace simdjson

namespace vk {
namespace event {
struct message_new_data {
    message_new_data(std::int64_t peer_id_, std::int64_t from_id_, std::string_view text_)
        : peer_id(peer_id_), from_id(from_id_), text(text_) { }
    std::int64_t peer_id;
    std::int64_t from_id;
    std::string text;
};

class vk_export message_new {
public:
    message_new(simdjson::dom::object&& event);
    message_new(
        std::int64_t peer_id, std::int64_t from_id, std::string_view text,
        simdjson::dom::array&& attachments
    );

    message_new reply() const;
    std::vector<std::shared_ptr<message_new>> fwd_messages() const;

    bool on_action(std::string_view action_name) const noexcept;

    std::string text()      const noexcept;
    std::int64_t from_id()  const noexcept;
    std::int64_t peer_id()  const noexcept;
    bool has_reply()        const noexcept;
    bool has_fwd_messages() const noexcept;
    bool has_action()       const noexcept;
    action::any_action action() const;
    attachment::attachments_t attachments() const;

private:
    void try_get_reply          (const simdjson::dom::object& reply);
    void try_get_fwd_messages   (const simdjson::dom::array& messages);
    void try_get_actions        (const simdjson::dom::object& action);

    std::shared_ptr<message_new_data> _message_obj;
    std::shared_ptr<message_new> _reply;
    action::any_action _action;
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
