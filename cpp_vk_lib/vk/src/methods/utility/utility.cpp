#include "vk/include/methods/utility/utility.hpp"
#include "vk/include/config/loader.hpp"

#include "runtime/include/net/network.hpp"
#include "runtime/include/string_utils/string_utils.hpp"

namespace vk::method {

utility::utility()
    : user_token_(config::user_token())
    , access_token_(config::access_token()) {}

utility::utility(std::string_view user_token)
    : user_token_(user_token.data())
    , access_token_(config::access_token()) {}

utility::~utility() = default;

std::string utility::append_url(std::string_view method)
{
    return runtime::string_utils::format("https://api.vk.com/method/{}?", method);
}

std::map<std::string, std::string>&& utility::user_args(std::map<std::string, std::string>&& params) const
{
    params.insert({{"access_token", user_token_}, {"v", API_V}});
    return std::move(params);
}

std::map<std::string, std::string>&& utility::group_args(std::map<std::string, std::string>&& params) const
{
    params.insert({{"access_token", access_token_}, {"v", API_V}});
    return std::move(params);
}

std::string utility::call(std::string_view method, std::map<std::string, std::string>&& params) const
{
    return runtime::network::request(append_url(method), std::move(params));
}

}// namespace vk::method