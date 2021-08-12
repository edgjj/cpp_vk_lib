#ifndef VK_EVENTS_HANDLERS_ATTACHMENT_HANDLER_HPP
#define VK_EVENTS_HANDLERS_ATTACHMENT_HANDLER_HPP

#include "vk/include/attachment/base.hpp"

#include <vector>

namespace simdjson::dom {
class array;
}// namespace simdjson::dom

namespace vk::event {

std::vector<attachment::attachment_ptr_t> get_attachments(const simdjson::dom::array& attachments);

}// namespace vk::event

#endif// VK_EVENTS_HANDLERS_ATTACHMENT_HANDLER_HPP

