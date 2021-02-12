#ifndef VK_EVENT_ATTACHMENT_HANDLER_H
#define VK_EVENT_ATTACHMENT_HANDLER_H

#include "misc/cppdefs.hpp"
#include "attachment/attachment.hpp"


namespace simdjson {
namespace dom {
class array;
} // namespace dom
} // namespace simdjson

namespace vk {
namespace event {
class vk_export message_new;
class vk_export wall_reply_new;
class vk_export wall_post_new;
} // namespace event
} // namespace vk

namespace vk {
namespace event {
struct vk_hidden attachment_handler {
private:
    attachment::attachments_t try_get(const simdjson::dom::array& attachments);

    friend class message_new;
    friend class wall_reply_new;
    friend class wall_post_new;
};
} // namespace event
} // namespace vk

#endif // VK_EVENT_ATTACHMENT_HANDLER_H
