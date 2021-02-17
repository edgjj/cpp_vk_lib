#include "api/service.hpp"

#include "logger/logger.hpp"


namespace {
class vk_hidden config {
public:
  friend class vk::service;

private:
  simdjson::dom::element element;
  simdjson::dom::parser parser;
  config(std::string_view path) noexcept {
    element = parser.load(path.data());
    logger(logflag::info | logflag::flush) << std::string("config successfully loaded (") + path.data() + std::string(")");
  }
  std::string_view load_access_token() const noexcept { return element["access_token"].get_string(); }
  std::string_view load_user_token()   const noexcept { return element["user_token"].get_string(); }
};
} // local namespace

vk::service::service() noexcept {
  static config config("./config.json");
  access_token = config.load_access_token();
  user_token   = config.load_user_token();
}
vk::service::service(std::string_view user_token_) {
  user_token = user_token_;
}
std::string vk::service::append_url(std::string_view method) const {
  return "https://api.vk.com/method/" + std::string(method) + '?';
}
std::map<std::string, std::string> vk::service::user_args(std::map<std::string, std::string>&& params) const {
  params.insert({{"access_token", user_token}, {"v", api_v}});
  return std::move(params);
}
std::map<std::string, std::string> vk::service::group_args(std::map<std::string, std::string>&& params) const {
  params.insert({{"access_token", access_token}, {"v", api_v}});
  return std::move(params);
}
simdjson::dom::object vk::service::call_and_parse(std::string_view method, std::map<std::string, std::string>&& params) {
  return parser.parse(call(method, std::move(params)));
}
std::string vk::service::call(std::string_view method, std::map<std::string, std::string>&& params) const {
  return net_client.request(append_url(method), std::move(params));
}
bool vk::service::error_returned(const simdjson::dom::object& response, std::int64_t error_code) {
  return response.begin().key() == "error" && response["error"]["error_code"].get_int64() == error_code;
}
