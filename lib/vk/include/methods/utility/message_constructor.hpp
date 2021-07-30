#ifndef VK_METHODS_UTILITY_MESSAGE_CONSTRUCTOR_HPP
#define VK_METHODS_UTILITY_MESSAGE_CONSTRUCTOR_HPP

#include "vk/include/attachment/attachment.hpp"
#include "vk/include/methods/utility/constructor.hpp"

namespace vk {
namespace method {
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
    message_constructor& attachments(attachment::attachments_t attachments);
    std::string execute();

private:
    std::string append_attachments_impl(attachment::attachments_t attachments) const;

    group_constructor m_constructor;
};

}// namespace method
}// namespace vk

#endif// VK_METHODS_UTILITY_MESSAGE_CONSTRUCTOR_HPP
