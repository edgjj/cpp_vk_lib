#pragma once

#include <string>
#include <memory>

#define vk_always_inline [[gnu::always_inline]]

namespace vk::lib       { class network; }
namespace simdjson::dom { class parser; }

namespace vk
{
class base_object
{
protected:
  explicit base_object() noexcept;
  virtual ~base_object();
  std::string append_url(std::string_view method) const;

  std::string access_token;
  std::string user_token;
  std::string api_v;
  std::string group_id;

  std::unique_ptr<lib::network> network;
  std::unique_ptr<simdjson::dom::parser> parser;
};
} // namespace vk
