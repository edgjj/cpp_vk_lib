#include "vk/include/attachment/attachment.hpp"

#include "spdlog/spdlog.h"

namespace vk::attachment {

wall::wall(int32_t id, int32_t from_id)
  : base("wall",   from_id, id)
{
    spdlog::trace("create attachment: {}", value());
}

}// namespace vk::attachment
