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
namespace context {

static inline const std::string_view oauth_link = "https://oauth.vk.com/";
static inline const std::string_view android_app_client_secret = "hHbZxrka2uZ6jB1inYsH";
static inline const std::string_view iphone_app_client_secret = "VeWdmVclDCtn6ihuP1nt";
static inline const std::string_view windows_app_client_secret = "AlVXZFMUqyrnABp8ncuU";

static inline const int32_t android_app_client_id = 2274003;
static inline const int32_t windows_app_client_id = 3697615;
static inline const int32_t iphone_app_client_id = 3140623;

}// namespace context

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
    client(std::string_view username, std::string_view password, target_client client_type);

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
    target_client client_type_;
    std::string username_;
    std::string password_;

    std::string target_client_secret_;
    int64_t target_client_id_;

    std::string pulled_token_;
    int64_t pulled_user_id_;
};

}// namespace oauth
}// namespace vk

#endif// VK_OAUTH_CLIENT_HPP
