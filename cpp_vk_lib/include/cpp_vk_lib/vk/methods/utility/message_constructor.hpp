#ifndef VK_METHODS_UTILITY_MESSAGE_CONSTRUCTOR_HPP
#define VK_METHODS_UTILITY_MESSAGE_CONSTRUCTOR_HPP

#include "cpp_vk_lib/vk/attachment/attachment.hpp"
#include "cpp_vk_lib/vk/methods/utility/constructor.hpp"

#include <vector>

namespace vk::method {
/*!
 * @brief Helper to work with message.send method.
 */
class message_constructor
{
public:
    static inline bool disable_mentions = true;
    static inline bool enable_mentions = false;

    explicit message_constructor(bool disable_mentions_flag);

    message_constructor& param(std::string_view lhs, std::string_view rhs);
    message_constructor& attachments(std::vector<attachment::attachment_ptr_t>&& attachments);
    std::string perform_request();

private:
    group_constructor constructor_;
};

}// namespace vk::method

#endif// VK_METHODS_UTILITY_MESSAGE_CONSTRUCTOR_HPP
