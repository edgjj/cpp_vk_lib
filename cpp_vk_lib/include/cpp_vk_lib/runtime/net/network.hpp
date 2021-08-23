#ifndef RUNTIME_NET_NETWORK_HPP
#define RUNTIME_NET_NETWORK_HPP

#include <map>
#include <string>
#include <string_view>
#include <vector>

extern bool cpp_vk_lib_curl_verbose;

namespace runtime::network {
/*!
 * \brief Perform HTTP POST request
 *
 * \param[in] host part of URL
 * \param[in] target list of arguments
 *            e.g {{"a", "1"}, {"b", "2"}} => a=1&b=2
 * \return response output
 */
std::string request(
    std::string_view host,
    std::map<std::string, std::string>&& target = {});
/*!
 * \brief Download from server to filename
 *
 * \note If file already exists, it will be overridden
 * \note This function follows redirects
 * \return -1 if file was not created or opened, 0 otherwise
 */
size_t download(
    std::string_view filename,
    std::string_view server);
/*!
 * \brief Download from server to in-memory buffer
 *
 * \note This function follows redirects
 * \note The buffer is flushing before writing
 * \return -1 if failed, 0 otherwise.
 */
size_t download(std::vector<uint8_t>& buffer, std::string_view server);
/*!
 * \brief Upload file from filename to server
 *
 * \param[in] field_name needed to correct file uploading
 * \return upload response
 */
std::string upload(
    std::string_view field_name,
    std::string_view filename,
    std::string_view server);
/*!
 * \brief Upload file from buffer to server
 *
 * \param[in] field_name needed to correct file uploading
 * \param[in] content_type e.g `text/html` or `multipart/form-data`
 * \return upload response
 */
std::string upload(
    const std::vector<uint8_t>& buffer,
    std::string_view field_name,
    std::string_view server,
    std::string_view content_type = "application/octet-stream");
/*!
 * \brief Execute HTTP POST request with text data
 *
 * \param[in] host part of URL
 * \param[in] URL payload, e.g JSON
 * \return response output
 */
std::string request_data(
    std::string_view host,
    std::string_view data);

}// namespace runtime::network

#endif// RUNTIME_NET_NETWORK_HPP
