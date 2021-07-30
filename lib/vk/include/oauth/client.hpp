#ifndef VK_OAUTH_CLIENT_HPP
#define VK_OAUTH_CLIENT_HPP

#include <memory>
#include <string>

namespace simdjson {
namespace dom {
class parser;
}// namespace dom
}// namespace simdjson

namespace vk {
namespace oauth {
enum class target_client : uint8_t
{
    android = (1 << 0),
    iphone  = (1 << 1),
    windows = (1 << 2)
};

/*!
 * @brief VK Oauth client.
 *
 * Example usage:
 *
 *  @code
 *  int main() {
 *      vk::oauth::client client("phone number", "password", vk::oauth::target_client::windows);
 *      client.pull();
 *      vk::messages messages(client.token());
 *  }
 *  @endcode
 */
class client
{
public:
    explicit client(std::string_view username_, std::string_view password_, target_client client_type_);

    ~client();
    /*!
     * @brief Try get user data.
     * @throws vk::exception::access_error with detailed description in case, when
     * wrong data were provided.
     */
    void pull();
    std::string token() const noexcept;
    int64_t user_id() const noexcept;

private:
    static inline const std::string_view m_oauth_link = "https://oauth.vk.com/";
    static inline const std::string_view m_android_app_client_secret = "hHbZxrka2uZ6jB1inYsH";
    static inline const std::string_view m_iphone_app_client_secret = "VeWdmVclDCtn6ihuP1nt";
    static inline const std::string_view m_windows_app_client_secret = "AlVXZFMUqyrnABp8ncuU";

    static inline const int32_t m_android_app_client_id = 2274003;
    static inline const int32_t m_windows_app_client_id = 3697615;
    static inline const int32_t m_iphone_app_client_id = 3140623;

    target_client m_client_type;
    std::string m_username;
    std::string m_password;

    std::string m_target_client_secret;
    int64_t m_target_client_id;

    std::string m_pulled_token;
    int64_t m_pulled_user_id;

    std::shared_ptr<simdjson::dom::parser> m_parser;
};

}// namespace oauth
}// namespace vk

#endif// VK_OAUTH_CLIENT_HPP
