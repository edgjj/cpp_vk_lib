#ifndef VK_METHODS_BASIC_HPP
#define VK_METHODS_BASIC_HPP

#include "vk/include/attachment/attachment.hpp"
#include "vk/include/exception/error_code.hpp"

#include <vector>

namespace simdjson {
namespace dom {
class object;
}// namespace dom
}// namespace simdjson

namespace vk {
namespace method {
namespace messages {

void send(int64_t peer_id, std::string_view text, bool mentions_flag = false);
void send(int64_t peer_id, std::string_view text, std::vector<attachment::attachment_ptr_t> list, bool mentions_flag = false);
void send(int64_t peer_id, std::string_view text, std::string_view keyboard_layout, bool mentions_flag = false);

}// namespace messages

namespace groups {

int64_t get_by_id(error_code& errc);
std::string get_long_poll_server(int64_t group_id);

}// namespace groups
}// namespace method
}// namespace vk

#endif// VK_METHODS_BASIC_HPP
