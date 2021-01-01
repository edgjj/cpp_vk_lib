#include <simdjson.h>

#include "vkapi/include/api/base_object.hpp"
#include "vkapi/include/lib/network.hpp"

namespace
{
class _config
{
public:
  friend class vk::base_object;

private:
  simdjson::dom::element element;
  simdjson::dom::parser parser;

  vk_always_inline _config(std::string_view file)             noexcept { element = parser.load(file.data()); }
  vk_always_inline std::string_view load_access_token() const noexcept { return static_cast<std::string_view>(element["access_token"]); }
  vk_always_inline std::string_view load_user_token()   const noexcept { return static_cast<std::string_view>(element["user_token"]); }
};
}

vk::base_object::base_object() noexcept
  : network(std::make_unique<lib::network>())
  , parser(std::make_unique<simdjson::dom::parser>())
{
  static _config config("./init.json");

  access_token = config.load_access_token();
  user_token   = config.load_user_token();
}

vk::base_object::~base_object() = default;

std::string vk::base_object::append_url(std::string_view method) const
{
  return "https://api.vk.com/method/" + std::string { method } + '?';
}
