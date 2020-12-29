#pragma once

#include "vkapi/include/updates/message_new.hpp"
//#include "vkapi/include/updates/wall_post_new.hpp"


namespace vk::update
{
class common
{
public:
  common(std::string_view ts, std::string_view update_type, std::string_view raw_json);

  std::string type() const noexcept;
  std::string ts() const noexcept;

  message_new get_message_update() const;
//  wall_post_new get_wall_post_update() const;

private:
  std::string _ts;
  std::string _update_type;
  std::string _raw_json;
};
}
