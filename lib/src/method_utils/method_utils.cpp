#include "simdjson.h"

#include "method_utils/method_utils.hpp"
#include "config/loader.hpp"


vk::method_utils::method_utils()
  : parser(std::make_unique<simdjson::dom::parser>())
  , net_client()
  , access_token(config::access_token())
  , user_token(config::user_token())
{ }

vk::method_utils::~method_utils() = default;

std::string vk::method_utils::append_url(std::string_view method) const {
  return "https://api.vk.com/method/" + std::string(method) + '?';
}
std::map<std::string, std::string> vk::method_utils::user_args(std::map<std::string, std::string>&& params) const {
  params.insert({{"access_token", user_token}, {"v", API_V}});
  return std::move(params);
}
std::map<std::string, std::string> vk::method_utils::group_args(std::map<std::string, std::string>&& params) const {
  params.insert({{"access_token", access_token}, {"v", API_V}});
  return std::move(params);
}
simdjson::dom::object vk::method_utils::call_and_parse(std::string_view method, std::map<std::string, std::string>&& params) const noexcept {
  return parser->parse(call(method, std::move(params)));
}
std::string vk::method_utils::call(std::string_view method, std::map<std::string, std::string>&& params) const {
  return net_client.request(append_url(method), std::move(params));
}
