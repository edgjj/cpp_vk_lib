#ifndef VK_OAUTH_H
#define VK_OAUTH_H

#include <string>

#include "net/client.hpp"


namespace simdjson {
namespace dom {
class parser;
} // namespace dom
} // namespace simdjson

namespace vk {
namespace oauth {
enum class target_client : std::uint8_t {
  android = (1 << 0),
  iphone  = (1 << 1),
  windows = (1 << 2)
};

/*!
 * @brief VK Oauth client.
 *
 * Example usage:
 *
 * int main() {
 *   vk::oauth::client client("phone number", "password", vk::oauth::target_client::windows);
 *   client.pull();
 *   vk::messages messages(client.token());
}
 */
class client {
public:
  explicit client(
    std::string_view username_,
    std::string_view password_,
    target_client client_type_
  );

  client() = default;
  client(const client&) = default;
  client(client&&) = default;
  client& operator=(const client&) = default;
  client& operator=(client&&) = default;
  ~client();
  /*!
   * @brief Try get user data.
   * @throws vk::exception::access_error with detailed description in case, when wrong data were provided.
   */
  void pull();
  std::string token() const noexcept;
  std::int64_t user_id() const noexcept;

private:
  static inline const std::string_view oauth_link = "https://oauth.vk.com/";
  static inline const std::string_view android_app_client_secret = "hHbZxrka2uZ6jB1inYsH";
  static inline const std::string_view iphone_app_client_secret  = "VeWdmVclDCtn6ihuP1nt";
  static inline const std::string_view windows_app_client_secret = "AlVXZFMUqyrnABp8ncuU";

  static inline const std::int32_t android_app_client_id = 2274003;
  static inline const std::int32_t windows_app_client_id = 3697615;
  static inline const std::int32_t iphone_app_client_id  = 3140623;

  target_client client_type;
  std::string username;
  std::string password;

  std::string target_client_secret;
  std::int64_t target_client_id;

  std::string pulled_token;
  std::int64_t pulled_user_id;

  std::shared_ptr<simdjson::dom::parser> parser;
  network_client net_client;
};
} // namespace oauth
} // namespace vk

#endif // VK_OAUTH_H
