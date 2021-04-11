#ifndef VK_METHOD_UTILITY_H
#define VK_METHOD_UTILITY_H

#include "net/client.hpp"

#include <string>

namespace simdjson {
namespace dom {
class object;
class parser;
}// namespace dom
}// namespace simdjson

namespace vk {
namespace method {
/*!
 * @brief The container of common functions and constants needed by various methods.
 */
class utility {
public:
  utility(std::string_view user_token);
  utility();

  utility(const utility&) = default;
  utility(utility&&) = default;
  utility& operator=(const utility&) = default;
  utility& operator=(utility&&) = default;
  ~utility();

  const std::map<std::string, std::string>& user_args(std::map<std::string, std::string>& params) const;
  const std::map<std::string, std::string>& user_args(std::map<std::string, std::string>&& params) const;
  const std::map<std::string, std::string>& group_args(std::map<std::string, std::string>& params) const;
  const std::map<std::string, std::string>& group_args(std::map<std::string, std::string>&& params) const;
  simdjson::dom::object call_and_parse(std::string_view method, std::map<std::string, std::string>&& params) const noexcept;
  simdjson::dom::object call_and_parse(std::string_view method, const std::map<std::string, std::string>& params) const noexcept;
  std::string call(std::string_view method, std::map<std::string, std::string>&& params) const;
  std::string call(std::string_view method, const std::map<std::string, std::string>& params) const;
  std::string append_url(std::string_view method) const;

  static inline const std::int64_t chat_id_constant = 2000000000;

private:
  vk::network_client net_client;
  std::string user_token;
  std::string access_token;
  mutable std::shared_ptr<simdjson::dom::parser> parser;
};
}// namespace method
}// namespace vk

#endif// VK_METHOD_UTILITY_H
