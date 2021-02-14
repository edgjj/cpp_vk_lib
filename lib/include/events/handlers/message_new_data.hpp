#ifndef VK_MESSAGE_NEW_DATA_H
#define VK_MESSAGE_NEW_DATA_H

#include <string>

#include "misc/cppdefs.hpp"


namespace vk {
namespace event {
/*!
 * @brief Wrapper to avoid meaningless and expensive copying by creating smart pointer to it.
 */
struct vk_hidden message_new_data {
  std::int64_t peer_id;
  std::int64_t from_id;
  std::string text;
};
} // namespace event
} // namespace vk


#endif // VK_MESSAGE_NEW_DATA_H
