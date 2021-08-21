#ifndef RUNTIME_NET_NETWORK_HPP
#define RUNTIME_NET_NETWORK_HPP

#include <map>
#include <string>
#include <string_view>
#include <vector>

namespace runtime::network {
/*!
 * @brief Execute HTTP POST request.
 * @return response output.
 */
std::string request(std::string_view host, std::map<std::string, std::string>&& target = {});
/*!
 * @brief Download file from server to filename.
 * @return -1 in case, when file was not created or opened, 0 otherwise.
 */
size_t download(std::string_view filename, std::string_view server);
/*!
 * @brief Download file from server to buffer.
 * @return -1 if failed, 0 otherwise.
 */
size_t download(std::vector<uint8_t>& buffer, std::string_view server);
/*!
 * @brief Upload file from filename to server.
 * @return upload response.
 */
std::string upload(std::string_view field_name, std::string_view filename, std::string_view server);
/*!
 * @brief Upload file from buffer to server.
 * @return upload response.
 */
std::string upload(std::string_view field_name, const std::vector<uint8_t>& buffer, std::string_view server, std::string_view type = "");
/*!
 * @brief Execute HTTP POST request with text data.
 * @return response output.
 */
std::string request_data(std::string_view host, std::string_view data);

}// namespace runtime::vk

#endif// RUNTIME_NET_NETWORK_HPP
