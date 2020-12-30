#pragma once

#include <string_view>

namespace vk::event
{
class wall_post_new
{
public:
  wall_post_new(std::string_view raw_json);

  long id()      const noexcept;
  long from_id() const noexcept;

private:
  long _id;
  long _from_id;
};
}
