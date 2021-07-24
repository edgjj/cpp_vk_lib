#ifndef VK_EVENTS_HANDLERS_ATTACHMENT_HANDLER_HPP
#define VK_EVENTS_HANDLERS_ATTACHMENT_HANDLER_HPP

#include "attachment/attachment.hpp"

namespace simdjson {
namespace dom {
class array;
}// namespace dom
}// namespace simdjson

namespace vk {
namespace event {
class message_new;
class wall_reply_new;
class wall_post_new;
}// namespace event
}// namespace vk

namespace vk {
namespace event {

class attachment_handler
{
private:
    attachment::attachments_t try_get(const simdjson::dom::array& attachments) const;

    friend class message_new;
    friend class wall_reply_new;
    friend class wall_post_new;
};

}// namespace event
}// namespace vk

#endif// VK_EVENTS_HANDLERS_ATTACHMENT_HANDLER_HPP

