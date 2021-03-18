#ifndef VK_NETWORK_CLIENT_H
#define VK_NETWORK_CLIENT_H

#include <string_view>
#include <memory>
#include <map>


namespace vk {
/*!
 * @brief The HTTPS client.
 */
class network_client {
public:
  /*!
   * @brief Execute HTTP POST request.
   * @param body    - link to page.
   * @param params  - parameters
   * @return response output.
   *
   * @example request("https://www.example.com?", {{"q","text"},{"length","50"}});
   */
  std::string request(std::string_view body, const std::map<std::string, std::string>& params = { }) const;
  /*!
   * @brief Download file frm server to filename.
   * @return -1 in case, when file was not created or opened, 0 otherwise.
   */
  std::size_t download(std::string_view filename, std::string_view server) const;
  /*!
   * @brief Upload file from filename to server.
   * @return upload response.
   */
  std::string upload(std::string_view field_name, std::string_view filename, std::string_view server) const;
  /*!
   * @brief Execute HTTP POST request with text data.
   * @return response output.
   */
  std::string request_data(std::string_view body, std::string_view data) const;
  /*!
   * @brief Unescape text.
   */
  static std::string unescape(std::string_view text);

private:
#if defined VK_CURL_DEBUG
  void debug(std::string_view template_text, std::string_view arg) const noexcept;
  void debug_error(std::string_view template_text, std::string_view arg) const noexcept;
#else
  void debug(std::string_view, std::string_view) const noexcept { }
  void debug_error(std::string_view, std::string_view) const noexcept { }
#endif // VK_CURL_DEBUG
};
} // namespace vk

#endif // VK_NETWORK_CLIENT_H
