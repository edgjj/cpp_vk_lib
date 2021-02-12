#ifndef VK_MESSAGE_NEW_H
#define VK_MESSAGE_NEW_H

#include "events/handlers/attachment_handler.hpp"
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

    std::string text()      const noexcept;
    std::string dump()      const noexcept;
    std::int64_t from_id()  const noexcept;
    std::int64_t peer_id()  const noexcept;
    bool has_reply()        const noexcept;
    bool has_fwd_messages() const noexcept;
    attachment::attachments_t attachments() const noexcept;

private:
    void try_get_reply          (const simdjson::dom::object& object);
    void try_get_fwd_messages   (const simdjson::dom::array& messages);

    std::int64_t _peer_id;
    std::int64_t _from_id;
    std::string _text;
    std::string _raw_json;
    std::shared_ptr<message_new> _reply;
    std::vector<std::shared_ptr<message_new>> _fwd_messages;
    attachment::attachments_t _attachments;
    bool _has_reply = false;
    bool _has_fwd_messages = false;

    attachment_handler att_handler;
};
} // namespace event
} // namespace vk

#endif // VK_MESSAGE_NEW_H
