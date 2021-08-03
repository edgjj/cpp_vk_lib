#ifndef VK_LONG_POLL_DATA_HPP
#define VK_LONG_POLL_DATA_HPP

#include <string>

namespace vk {
/*!
 * @brief Wrapper for data returned by group long poll.
 */
struct long_poll_data
{
    std::string key;
    std::string server;
    std::string ts;
};

}// namespace vk

#endif// VK_LONG_POLL_DATA_HPP
