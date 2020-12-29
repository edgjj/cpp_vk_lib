#pragma once

#include <list>
#include "vkapi/include/api/base_object.hpp"
#include "vkapi/include/updates/common_update.hpp"

namespace vk
{
struct long_poll_data
{
  std::string key;
  std::string server;
  std::string ts;
};

class long_poll_api : private base_object
{
public:
  long_poll_data get_server();
  std::list<update::common> listen(const long_poll_data& data);
};
}
