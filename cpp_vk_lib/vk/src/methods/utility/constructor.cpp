#include "vk/include/methods/utility/constructor.hpp"

#include "runtime/include/misc/cppdefs.hpp"
#include "runtime/include/net/network.hpp"

#include "vk/include/api_constants.hpp"

static std::string append_url(std::string_view method)
{
    return runtime::string_utils::format("https://api.vk.com/method/{}?", method);
}

static std::string call(std::string_view method, std::map<std::string, std::string>&& params)
{
    return runtime::network::request(append_url(method), std::move(params));
}

namespace vk::method::policy {

std::string group_api::execute(
    std::map<std::string, std::string>&& params,
    const std::string& method,
    const std::string& access_token,
    const std::string& user_token
) {
    VK_UNUSED(user_token);
    params.insert({{"access_token", access_token}, {"v", api_constants::api_version}});
    return call(method, std::move(params));
}

std::string user_api::execute(
    std::map<std::string, std::string>&& params,
    const std::string& method,
    const std::string& access_token,
    const std::string& user_token
) {
    VK_UNUSED(access_token);
    params.insert({{"access_token", user_token}, {"v", api_constants::api_version}});
    return call(method, std::move(params));
}

std::string do_not_use_api_link::execute(
    std::map<std::string, std::string>&& params,
    const std::string& method,
    const std::string& access_token,
    const std::string& user_token
) {
    VK_UNUSED(user_token);
    VK_UNUSED(access_token);
    return runtime::network::request(method, std::move(params));
}

}// namespace vk::method::policy

namespace vk::method {

template<typename ExecutionPolicy>
constructor<ExecutionPolicy>::constructor()
    : user_token_(config::user_token())
    , access_token_(config::access_token()) {}

template<typename ExecutionPolicy>
constructor<ExecutionPolicy>::constructor(std::string_view user_token)
   : user_token_(user_token)
   , access_token_(config::access_token()) {}

template<typename ExecutionPolicy>
constructor<ExecutionPolicy>& constructor<ExecutionPolicy>::method(std::string_view method)
{
    method_.assign(method.data(), method.size());
    return *this;
}

template<typename ExecutionPolicy>
constructor<ExecutionPolicy>& constructor<ExecutionPolicy>::param(std::string_view key, std::string_view value)
{
    params_.emplace(key, value);
    return *this;
}

template<typename ExecutionPolicy>
constructor<ExecutionPolicy>& constructor<ExecutionPolicy>::append_map(std::map<std::string, std::string>&& additional_params)
{
    params_.merge(std::move(additional_params));
    return *this;
}

template<typename ExecutionPolicy>
std::string constructor<ExecutionPolicy>::perform_request()
{
    return ExecutionPolicy::execute(std::move(params_), method_, access_token_, user_token_);
}

}// namespace vk::method

template class vk::method::constructor<vk::method::policy::user_api>;
template class vk::method::constructor<vk::method::policy::group_api>;
template class vk::method::constructor<vk::method::policy::do_not_use_api_link>;
