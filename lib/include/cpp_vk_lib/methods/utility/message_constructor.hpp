#ifndef VK_MESSAGE_CONSTRUCTOR_H
#define VK_MESSAGE_CONSTRUCTOR_H

#include "attachment/attachment.hpp"

#include <iostream>
#include <map>
#include <numeric>
#include <string>

namespace vk {
namespace method {

class message_constructor
{
public:
    static inline bool disable_mentions = true;
    static inline bool enable_mentions = false;

    message_constructor(bool disable_mentions_flag)
      : m_params()
    {
        m_params.emplace("random_id", "0");
        if (disable_mentions_flag)
        {
            m_params.emplace("disable_mentions", "1");
        }
        else
        {
            m_params.emplace("disable_mentions", "0");
        }
    }

    void append(std::string_view lhs, std::string_view rhs)
    {
        m_params.emplace(lhs, rhs);
    }
    /*!
     * @note Additional_params should be moved.
     */
    void append_map(std::map<std::string, std::string> additional_params)
    {
        m_params.merge(std::move(additional_params));
    }

    template <typename _Attachment_List>
    void append_attachments(_Attachment_List&& attachments)
    {
        m_params.emplace("attachment", append_attachments_impl(std::forward<_Attachment_List>(attachments)).data());
    }

    std::map<std::string, std::string>&& consume_map() noexcept
    {
        return std::move(m_params);
    }
    std::map<std::string, std::string> map() const noexcept
    {
        return m_params;
    }

private:
    template <typename _Attachment_T>
    std::string append_attachments_impl(_Attachment_T&& attachments) const
    {
        std::string result;
        result.reserve(attachments.size() * 20);
        for (auto& attachment : attachments)
        {
            result += attachment->value();
            result += ',';
        }
        return result;
    }
    std::map<std::string, std::string> m_params;
};
}// namespace method
}// namespace vk

#endif// VK_MESSAGE_CONSTRUCTOR_H
