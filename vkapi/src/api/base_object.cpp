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

  vk_always_inline _config(std::string_view file)        noexcept {   element = parser.load(file.data()); }
  vk_always_inline std::string load_access_token() const noexcept { return static_cast<std::string>(element["token"]["access_token"]); }
  vk_always_inline std::string load_user_token()   const noexcept { return static_cast<std::string>(element["token"]["user_token"]); }
  vk_always_inline std::string load_api_v()        const noexcept { return static_cast<std::string>(element["api_v"]); }
  vk_always_inline std::string load_group_id()     const noexcept { return static_cast<std::string>(element["group_id"]); }
};
}

vk::base_object::base_object() noexcept
  : network(std::make_unique<lib::network>())
  , parser(std::make_unique<simdjson::dom::parser>())
{
  static _config config("./init.json");

  access_token = config.load_access_token();
  user_token   = config.load_user_token();
  api_v        = config.load_api_v();
  group_id     = config.load_group_id();
}

vk::base_object::~base_object() = default;

std::string vk::base_object::append_url(std::string_view method) const
{
  return "https://api.vk.com/method/" + std::string { method } + '?';
}
