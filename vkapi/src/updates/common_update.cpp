#include "vkapi/include/updates/common_update.hpp"

vk::update::common::common(std::string_view ts, std::string_view update_type, std::string_view raw_json)
  : _ts(ts)
  , _update_type(update_type)
  , _raw_json(raw_json)
{ }

vk::update::message_new vk::update::common::get_message_update() const
{
  return vk::update::message_new(_raw_json);
}

//vk::update::wall_post_new vk::update::common::get_wall_post_update() const
//{
//  return vk::update::wall_post_new();
//}

std::string vk::update::common::type() const noexcept
{
  return _update_type;
}

std::string vk::update::common::ts() const noexcept
{
  return _ts;
}
