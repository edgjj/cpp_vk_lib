#ifndef VK_METHODS_UTILITY_CONSTRUCTOR_HPP
#define VK_METHODS_UTILITY_CONSTRUCTOR_HPP

#include "cpp_vk_lib/runtime/net/network.hpp"

namespace vk::method::policy {

struct group_api
{
    static std::string execute(
        std::map<std::string, std::string>&& params,
        const std::string& method,
        const std::string& access_token,
        const std::string& user_token
    );
};
struct user_api
{
    static std::string execute(
        std::map<std::string, std::string>&& params,
        const std::string& method,
        const std::string& access_token,
        const std::string& user_token
    );
};
struct do_not_use_api_link
{
    static std::string execute(
        std::map<std::string, std::string>&& params,
        const std::string& method,
        const std::string& access_token,
        const std::string& user_token
    );
};

}// namespace vk::method::policy

namespace vk::method {

template <typename ExecutionPolicy>
class constructor
{
public:
    constructor();
    constructor(std::string_view user_token);

    constructor& method(std::string_view method);

    constructor& param(std::string_view key, std::string_view value);

    constructor& append_map(std::map<std::string, std::string>&& additional_params);

    std::string perform_request();

private:
    std::string user_token_;
    std::string access_token_;
    std::string method_{};
    std::map<std::string, std::string> params_{};
};

using user_constructor = constructor<policy::user_api>;
using group_constructor = constructor<policy::group_api>;
using raw_constructor = constructor<policy::do_not_use_api_link>;

}// namespace vk::method

#endif// VK_METHODS_UTILITY_CONSTRUCTOR_HPP
