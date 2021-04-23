#ifndef VK_LONG_POLL_DATA_H
#define VK_LONG_POLL_DATA_H

#include <string>

namespace vk {
namespace long_poll {
/*!
 * @brief Wrapper for data returned by group long poll.
 */
struct data
{
    std::string key;
    std::string server;
    std::string ts;
};
}// namespace long_poll
}// namespace vk
#endif// VK_LONG_POLL_DATA_H
