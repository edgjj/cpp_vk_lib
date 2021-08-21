#include "cpp_vk_lib/vk/attachment/attachment.hpp"

#include "spdlog/spdlog.h"

namespace vk::attachment {

audio::audio(int32_t owner_id, int32_t id)
  : base("audio", owner_id, id)
{
    spdlog::trace("create attachment: {}", value());
}

}// namespace vk::attachment
