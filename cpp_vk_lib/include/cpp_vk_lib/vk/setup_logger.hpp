#ifndef VK_SETUP_LOGGER_HPP
#define VK_SETUP_LOGGER_HPP

#include "spdlog/spdlog.h"

namespace vk {

inline void setup_logger(spdlog::level::level_enum level)
{
    spdlog::set_level(level);
}

}// namespace vk

#endif// VK_SETUP_LOGGER_HPP
