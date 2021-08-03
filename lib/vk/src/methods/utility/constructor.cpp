#include "vk/include/methods/utility/constructor.hpp"

#include "runtime/include/misc/cppdefs.hpp"
#include "runtime/include/net/network.hpp"

std::string vk::method::policy::group_api::execute(const utility& method_util, std::string_view method, std::map<std::string, std::string>& params)
{
    return method_util.call(method, method_util.group_args(params));
}

std::string vk::method::policy::user_api::execute(const utility& method_util, std::string_view method, std::map<std::string, std::string>& params)
{
    return method_util.call(method, method_util.user_args(params));
}

std::string vk::method::policy::do_not_use_api_link::execute(const utility& method_util, std::string_view method, std::map<std::string, std::string>& params)
{
    VK_UNUSED(method_util);
    return runtime::network::request(method, params);
}

template<typename ExecutionPolicy>
vk::method::constructor<ExecutionPolicy>::constructor()
    : m_method_util() {}

template<typename ExecutionPolicy>
vk::method::constructor<ExecutionPolicy>::constructor(std::string_view user_token)
   : m_method_util(user_token) {}

template<typename ExecutionPolicy>
vk::method::constructor<ExecutionPolicy>& vk::method::constructor<ExecutionPolicy>::method(std::string_view method) &
{
    m_method.assign(method.data(), method.size());
    return *this;
}

template<typename ExecutionPolicy>
 vk::method::constructor<ExecutionPolicy>&& vk::method::constructor<ExecutionPolicy>::method(std::string_view method) &&
{
    m_method.assign(method.data(), method.size());
    return static_cast<vk::method::constructor<ExecutionPolicy>&&>(*this);
}

template<typename ExecutionPolicy>
 vk::method::constructor<ExecutionPolicy>& vk::method::constructor<ExecutionPolicy>::param(std::string_view key, std::string_view value) &
{
    m_params.emplace(key, value);
    return *this;
}

template<typename ExecutionPolicy>
 vk::method::constructor<ExecutionPolicy>&& vk::method::constructor<ExecutionPolicy>::param(std::string_view key, std::string_view value) &&
{
    m_params.emplace(key, value);
    return static_cast<vk::method::constructor<ExecutionPolicy>&&>(*this);
}

template<typename ExecutionPolicy>
 vk::method::constructor<ExecutionPolicy>& vk::method::constructor<ExecutionPolicy>::append_map(std::map<std::string, std::string> additional_params) &
{
    m_params.merge(std::move(additional_params));
    return *this;
}

template<typename ExecutionPolicy>
 vk::method::constructor<ExecutionPolicy>&& vk::method::constructor<ExecutionPolicy>::append_map(std::map<std::string, std::string> additional_params) &&
{
    m_params.merge(std::move(additional_params));
    return static_cast<vk::method::constructor<ExecutionPolicy>&&>(*this);
}

template<typename ExecutionPolicy>
std::string vk::method::constructor<ExecutionPolicy>::perform_request() &
{
    std::string result = ExecutionPolicy::execute(m_method_util, m_method, m_params);
    m_params.clear();
    return result;
}

template<typename ExecutionPolicy>
std::string vk::method::constructor<ExecutionPolicy>::perform_request() &&
{
    return ExecutionPolicy::execute(m_method_util, m_method, m_params);
}

template class vk::method::constructor<vk::method::policy::user_api>;
template class vk::method::constructor<vk::method::policy::group_api>;
template class vk::method::constructor<vk::method::policy::do_not_use_api_link>;
