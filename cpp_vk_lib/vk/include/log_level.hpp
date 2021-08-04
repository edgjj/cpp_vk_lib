#ifndef VK_LOG_LEVEL_HPP
#define VK_LOG_LEVEL_HPP

#include "spdlog/spdlog.h"

namespace vk {

namespace log_level {

inline void trace() {
    spdlog::set_level(static_cast<spdlog::level::level_enum>(SPDLOG_LEVEL_TRACE));
}
inline void debug() {
    spdlog::set_level(static_cast<spdlog::level::level_enum>(SPDLOG_LEVEL_DEBUG));
}
inline void info() {
    spdlog::set_level(static_cast<spdlog::level::level_enum>(SPDLOG_LEVEL_INFO));
}
inline void warn() {
    spdlog::set_level(static_cast<spdlog::level::level_enum>(SPDLOG_LEVEL_WARN));
}
inline void error() {
    spdlog::set_level(static_cast<spdlog::level::level_enum>(SPDLOG_LEVEL_ERROR));
}
inline void critical() {
    spdlog::set_level(static_cast<spdlog::level::level_enum>(SPDLOG_LEVEL_CRITICAL));
}
inline void disable() {
    spdlog::set_level(static_cast<spdlog::level::level_enum>(SPDLOG_LEVEL_OFF));
}

}// namespace log_level
}// namespace vk

#endif // VK_LOG_LEVEL_HPP
