#include "vk/include/attachment/base.hpp"

#include "spdlog/spdlog.h"

namespace vk::attachment {

video::video(int32_t owner_id, int32_t id)
  : base("video", owner_id, id)
{
    spdlog::trace("create attachment: {}", value());
}

}// namespace vk::attachment