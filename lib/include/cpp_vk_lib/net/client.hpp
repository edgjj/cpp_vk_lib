#ifndef VK_NETWORK_CLIENT_H
#define VK_NETWORK_CLIENT_H

#include <string_view>
#include <memory>
#include <map>

#include "misc/cppdefs.hpp"

#if defined VK_CURL_DEBUG
#include "logger/logger.hpp"
#endif // VK_CURL_DEBUG


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
  template <typename... Args>
  void debug(Args&&... args) const noexcept {
    logger(logflag::debug | logflag::spaces).print_pack(args...);
  }
  template <typename... Args>
  void debug_error(Args&&... args) const noexcept {
    logger(logflag::error | logflag::spaces).print_pack(args...);
  }
#else
  template <typename... Args>
  constexpr void debug(Args&&...) const noexcept { }
  template <typename... Args>
  constexpr void debug_error(Args&&...) const noexcept { }
#endif // VK_CURL_DEBUG
};
} // namespace vk

#endif // VK_NETWORK_CLIENT_H
