#ifndef VK_SETUP_LOGGER_HPP
#define VK_SETUP_LOGGER_HPP

#include "spdlog/spdlog.h"

namespace vk {

inline void setup_logger(std::string_view level)
{
    if (level == "off") {
        spdlog::set_level(static_cast<spdlog::level::level_enum>(SPDLOG_LEVEL_OFF));
    } else if (level == "critical") {
        spdlog::set_level(static_cast<spdlog::level::level_enum>(SPDLOG_LEVEL_CRITICAL));
    } else if (level == "error") {
        spdlog::set_level(static_cast<spdlog::level::level_enum>(SPDLOG_LEVEL_ERROR));
    } else if (level == "warn") {
        spdlog::set_level(static_cast<spdlog::level::level_enum>(SPDLOG_LEVEL_WARN));
    } else if (level == "info") {
        spdlog::set_level(static_cast<spdlog::level::level_enum>(SPDLOG_LEVEL_INFO));
    } else if (level == "debug") {
        spdlog::set_level(static_cast<spdlog::level::level_enum>(SPDLOG_LEVEL_DEBUG));
    } else if (level == "trace") {
        spdlog::set_level(static_cast<spdlog::level::level_enum>(SPDLOG_LEVEL_TRACE));
    } else {
        spdlog::set_level(static_cast<spdlog::level::level_enum>(SPDLOG_LEVEL_INFO));
    }
}

}// namespace vk

#endif// VK_SETUP_LOGGER_HPP
