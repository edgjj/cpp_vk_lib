#ifndef VK_METHODS_UTILITY_CONSTRUCTOR_HPP
#define VK_METHODS_UTILITY_CONSTRUCTOR_HPP

#include "runtime/include/net/network.hpp"

#include "vk/include/methods/utility/utility.hpp"

namespace vk {
namespace method {

namespace policy {

struct group_api
{
    static std::string execute(const vk::method::utility& method_util, std::string_view method, std::map<std::string, std::string>& params);
};
struct user_api
{
    static std::string execute(const vk::method::utility& method_util, std::string_view method, std::map<std::string, std::string>& params);
};
struct do_not_use_api_link
{
    static std::string execute(const vk::method::utility& method_util, std::string_view method, std::map<std::string, std::string>& params);
};

} // namespace policy

template <typename ExecutionPolicy>
class constructor
{
public:
    constructor();
    constructor(std::string_view user_token);

    constructor&  method(std::string_view method) & ;
    constructor&& method(std::string_view method) &&;

    constructor&  param(std::string_view key, std::string_view value) & ;
    constructor&& param(std::string_view key, std::string_view value) &&;

    constructor&  append_map(std::map<std::string, std::string> additional_params) & ;
    constructor&& append_map(std::map<std::string, std::string> additional_params) &&;

    std::string perform_request()  &;
    std::string perform_request() &&;

private:
    vk::method::utility m_method_util;
    std::string m_method{};
    std::map<std::string, std::string> m_params{};
};

using user_constructor = constructor<policy::user_api>;
using group_constructor = constructor<policy::group_api>;
using raw_constructor = constructor<policy::do_not_use_api_link>;

}// namespace method
}// namespace vk

#endif// VK_METHODS_UTILITY_CONSTRUCTOR_HPP
