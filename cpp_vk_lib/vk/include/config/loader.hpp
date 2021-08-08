#ifndef VK_CONFIG_LOADER_HPP
#define VK_CONFIG_LOADER_HPP

#include <string>

namespace vk {
namespace config {

void load(std::string_view path);
void load_string(std::string_view string);
void set_user_token(std::string_view token);

std::string password();
std::string username();
std::string user_token();
std::string access_token();
std::string log_path();
size_t num_workers();

}// namespace config
}// namespace vk

#endif// VK_CONFIG_LOADER_HPP
