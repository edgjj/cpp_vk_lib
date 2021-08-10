#ifndef VK_METHODS_UTILITY_MESSAGE_CONSTRUCTOR_HPP
#define VK_METHODS_UTILITY_MESSAGE_CONSTRUCTOR_HPP

#include "vk/include/attachment/attachment.hpp"
#include "vk/include/methods/utility/constructor.hpp"

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

    message_constructor(bool disable_mentions_flag);

    message_constructor& param(std::string_view lhs, std::string_view rhs);
    /*!
     * Move or copy is your choice.
     */
    message_constructor& append_map(std::map<std::string, std::string> additional_params);
    message_constructor& attachments(std::vector<attachment::attachment_ptr_t> attachments);
    std::string perform_request();

private:
    static std::string append_attachments_impl(std::vector<attachment::attachment_ptr_t> attachments) ;

    group_constructor constructor_;
};

}// namespace vk::method

#endif// VK_METHODS_UTILITY_MESSAGE_CONSTRUCTOR_HPP
