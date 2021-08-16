#ifndef VK_API_CONSTANTS_HPP
#define VK_API_CONSTANTS_HPP

#include <string_view>

namespace vk::api_constants {

static inline const char api_version[] = "5.130";

static inline const std::string_view oauth_link = "https://oauth.vk.com/";

static inline const char android_app_client_secret[] = "hHbZxrka2uZ6jB1inYsH";
static inline const char iphone_app_client_secret[]  = "VeWdmVclDCtn6ihuP1nt";
static inline const char windows_app_client_secret[] = "AlVXZFMUqyrnABp8ncuU";
static inline const int32_t android_app_client_id = 2274003;

static inline const int32_t windows_app_client_id = 3697615;
static inline const int32_t iphone_app_client_id = 3140623;

static inline const uint64_t chat_id_constant = 2000000000;

}// namespace vk::constants

#endif //VK_API_CONSTANTS_HPP
