#include "simdjson.h"

#include "method_utils/method_utils.hpp"
#include "config/loader.hpp"


vk::method_utils::method_utils()
  : parser(std::make_unique<simdjson::dom::parser>())
{ }

vk::method_utils::~method_utils() = default;

std::string vk::method_utils::append_url(std::string_view method) const {
  return "https://api.vk.com/method/" + std::string(method) + '?';
}
std::map<std::string, std::string> vk::method_utils::user_args(std::map<std::string, std::string>&& params) const {
  params.insert({{"access_token", vk::config::access_token()}, {"v", API_V}});
  return std::move(params);
}
std::map<std::string, std::string> vk::method_utils::group_args(std::map<std::string, std::string>&& params) const {
  params.insert({{"access_token", vk::config::access_token()}, {"v", API_V}});
  return std::move(params);
}
simdjson::dom::object vk::method_utils::call_and_parse(std::string_view method, std::map<std::string, std::string>&& params) {
  return parser->parse(call(method, std::move(params)));
}
std::string vk::method_utils::call(std::string_view method, std::map<std::string, std::string>&& params) const {
  return net_client.request(append_url(method), std::move(params));
}
bool vk::method_utils::error_returned(const simdjson::dom::object& response, std::int64_t error_code) {
  return response.begin().key() == "error" && response["error"]["error_code"].get_int64() == error_code;
}
