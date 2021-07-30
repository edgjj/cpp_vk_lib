#ifndef VK_METHODS_UTILITY_CONSTRUCTOR_HPP
#define VK_METHODS_UTILITY_CONSTRUCTOR_HPP

#include "runtime/include/misc/cppdefs.hpp"
#include "runtime/include/net/network.hpp"

#include "vk/include/methods/utility/utility.hpp"

namespace vk {
namespace method {
namespace policy {

class group_api
{
public:
    static std::string execute(const vk::method::utility& method_util, std::string_view method, std::map<std::string, std::string>& params)
    {
        return method_util.call(method, method_util.group_args(params));
    }
};

class user_api
{
public:
    static std::string execute(const vk::method::utility& method_util, std::string_view method, std::map<std::string, std::string>& params)
    {
        return method_util.call(method, method_util.user_args(params));
    }
};

class do_not_use_api_link
{
public:
    static std::string execute(const vk::method::utility& method_util, std::string_view method, std::map<std::string, std::string>& params)
    {
        VK_UNUSED(method_util);
        return runtime::network::request(method, params);
    }
};

} // namespace policy

template <typename ExecutionPolicy>
class constructor
{
public:
    explicit constructor()
        : m_method_util() {}

    explicit constructor(std::string_view user_token)
        : m_method_util(user_token) {}

    constructor& method(std::string_view method)
    {
        m_method = method;
        return *this;
    }

    constructor& param(std::string_view key, std::string_view value)
    {
        m_params.emplace(key, value);
        return *this;
    }

    constructor& append_map(std::map<std::string, std::string> additional_params)
    {
        m_params.merge(std::move(additional_params));
        return *this;
    }

    std::string perform_request()
    {
        const std::string result = ExecutionPolicy::execute(m_method_util, m_method, m_params);
        m_params.clear();
        return result;
    }

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
