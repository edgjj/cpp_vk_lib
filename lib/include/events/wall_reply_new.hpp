#ifndef VK_WALL_REPLY_NEW_H
#define VK_WALL_REPLY_NEW_H

#include "attachment/attachment.hpp"
#include "events/handlers/attachment_handler.hpp"
#include "misc/cppdefs.hpp"


namespace simdjson {
namespace dom {
class object;
} // namespace dom
} // namespace simdjson

namespace vk {
namespace event {
class vk_export wall_reply_new {
public:
    explicit wall_reply_new(simdjson::dom::object&& event);
    std::int64_t id() const noexcept;
    std::int64_t from_id() const noexcept;
    std::int64_t post_id() const noexcept;
    std::int64_t owner_id() const noexcept;
    std::string text() const noexcept;
    attachment::attachments_t attachments() const noexcept;

private:
    std::int64_t _id;
    std::int64_t _post_id;
    std::int64_t _from_id;
    std::int64_t _owner_id;
    std::string _text;
    attachment::attachments_t _attachments;

    attachment_handler att_handler;
};
} // namespace event
} // namespace vk

#endif // VK_WALL_REPLY_NEW_H
