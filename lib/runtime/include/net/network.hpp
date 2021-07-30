#ifndef VK_NET_NETWORK_HPP
#define VK_NET_NETWORK_HPP

#include <map>
#include <string_view>

namespace runtime {
namespace network {
/*!
 * @brief Execute HTTP POST request.
 * @return response output.
 *
 * @example request("https://www.example.com?", {{"q","text"},{"length","50"}});
 */
std::string request(std::string_view host, const std::map<std::string, std::string>& target = {});
/*!
 * @brief Download file from server to filename.
 * @return -1 in case, when file was not created or opened, 0 otherwise.
 */
size_t download(std::string_view filename, std::string_view server);
/*!
 * @brief Upload file from filename to server.
 * @return upload response.
 */
std::string upload(std::string_view field_name, std::string_view filename, std::string_view server);
/*!
 * @brief Execute HTTP POST request with text data.
 * @return response output.
 */
std::string request_data(std::string_view host, std::string_view data);

}// namespace network
}// namespace vk

#endif// VK_NET_NETWORK_HPP
