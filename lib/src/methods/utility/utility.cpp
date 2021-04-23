#include "methods/utility/utility.hpp"

#include "config/loader.hpp"
#include "simdjson.h"

vk::method::utility::utility()
  : net_client()
  , user_token(config::user_token())
  , access_token(config::access_token())
  , parser(std::make_shared<simdjson::dom::parser>())
{}

vk::method::utility::utility(std::string_view user_token_)
  : net_client()
  , user_token(user_token_.data())
  , access_token(config::access_token())
  , parser(std::make_shared<simdjson::dom::parser>())
{}

vk::method::utility::~utility() = default;

std::string vk::method::utility::append_url(std::string_view method) const
{
    return "https://api.vk.com/method/" + std::string(method) + '?';
}

const std::map<std::string, std::string>& vk::method::utility::user_args(std::map<std::string, std::string>& params) const
{
    params.insert({{"access_token", user_token}, {"v", API_V}});
    return params;
}

const std::map<std::string, std::string>& vk::method::utility::user_args(std::map<std::string, std::string>&& params) const
{
    params.insert({{"access_token", user_token}, {"v", API_V}});
    return params;
}

const std::map<std::string, std::string>& vk::method::utility::group_args(std::map<std::string, std::string>& params) const
{
    params.insert({{"access_token", access_token}, {"v", API_V}});
    return params;
}

const std::map<std::string, std::string>& vk::method::utility::group_args(std::map<std::string, std::string>&& params) const
{
    params.insert({{"access_token", access_token}, {"v", API_V}});
    return params;
}

simdjson::dom::object
vk::method::utility::call_and_parse(std::string_view method, std::map<std::string, std::string>&& params) const noexcept
{
    return parser->parse(call(method, std::move(params)));
}

simdjson::dom::object
vk::method::utility::call_and_parse(std::string_view method, const std::map<std::string, std::string>& params) const noexcept
{
    return parser->parse(call(method, params));
}

std::string vk::method::utility::call(std::string_view method, std::map<std::string, std::string>&& params) const
{
    return net_client.request(append_url(method), std::move(params));
}

std::string vk::method::utility::call(std::string_view method, const std::map<std::string, std::string>& params) const
{
    return net_client.request(append_url(method), params);
}
