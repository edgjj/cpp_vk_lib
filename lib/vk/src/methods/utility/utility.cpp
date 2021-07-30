#include "vk/include/methods/utility/utility.hpp"
#include "vk/include/config/loader.hpp"

#include "runtime/include/net/network.hpp"

#include "simdjson.h"

vk::method::utility::utility()
    : m_user_token(config::user_token())
    , m_access_token(config::access_token())
    , m_parser(std::make_shared<simdjson::dom::parser>()) {}

vk::method::utility::utility(std::string_view user_token_)
    : m_user_token(user_token_.data())
    , m_access_token(config::access_token())
    , m_parser(std::make_shared<simdjson::dom::parser>()) {}

vk::method::utility::~utility() = default;

std::string vk::method::utility::append_url(std::string_view method) const
{
    return "https://api.vk.com/method/" + std::string(method) + '?';
}

std::map<std::string, std::string>& vk::method::utility::user_args(std::map<std::string, std::string>& params) const
{
    params.insert({{"access_token", m_user_token}, {"v", API_V}});
    return params;
}

std::map<std::string, std::string>& vk::method::utility::group_args(std::map<std::string, std::string>& params) const
{
    params.insert({{"access_token", m_access_token}, {"v", API_V}});
    return params;
}

std::string vk::method::utility::call(std::string_view method, std::map<std::string, std::string> params) const
{
    return runtime::network::request(append_url(method), std::move(params));
}
