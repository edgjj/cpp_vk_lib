#ifndef VK_EVENTS_HANDLERS_ATTACHMENT_HANDLER_HPP
#define VK_EVENTS_HANDLERS_ATTACHMENT_HANDLER_HPP

#include "vk/include/attachment/attachment.hpp"

#include <vector>

namespace simdjson {
namespace dom {
class array;
}// namespace dom
}// namespace simdjson

namespace vk {
namespace event {

std::vector<attachment::attachment_ptr_t> get_attachments(const simdjson::dom::array& attachments);

}// namespace event
}// namespace vk

#endif// VK_EVENTS_HANDLERS_ATTACHMENT_HANDLER_HPP

