#ifndef VK_CONFIG_LOADER_HPP
#define VK_CONFIG_LOADER_HPP

#include <string>

namespace vk::config {

/*!
 * \brief Load config from file.
 *
 * \note If config already exists, it will be overridden.
 */
void load(std::string_view path);
/*!
 * \brief Load config from string.
 *
 * \note If config already exists, it will be overridden.
 */
void load_string(std::string_view string);
void override_user_token(std::string_view token);

std::string password();
std::string username();
std::string user_token();
std::string access_token();
std::string log_path();
size_t num_workers();

}// namespace vk::config

#endif// VK_CONFIG_LOADER_HPP
