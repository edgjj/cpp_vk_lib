#include "vk/include/attachment/base.hpp"

#include "spdlog/spdlog.h"

namespace vk::attachment {

document::document(int32_t owner_id, int32_t id, std::string_view url)
  : base("doc", owner_id, id), raw_url_(url)
{
    spdlog::trace("create attachment: {}", value());
}

const std::string& document::raw_url() const noexcept
{
    return raw_url_;
}

}// namespace vk::attachment