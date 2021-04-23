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
    message_constructor(const message_constructor&) = default;
    message_constructor(message_constructor&&) = default;
    message_constructor& operator=(const message_constructor&) = default;
    message_constructor& operator=(message_constructor&&) = default;
    ~message_constructor() = default;

    using parameter_t = std::map<std::string, std::string>;

    static inline bool disable_mentions = true;
    static inline bool enable_mentions = false;

    message_constructor(bool disable_mentions_flag)
      : params()
    {
        params.emplace("random_id", "0");
        if (disable_mentions_flag)
        {
            params.emplace("disable_mentions", "1");
        }
        else
        {
            params.emplace("disable_mentions", "0");
        }
    }

    void append(std::pair<std::string, std::string>&& pair)
    {
        params.emplace(std::move(pair));
    }
    void append(const std::pair<std::string, std::string>& pair)
    {
        params.emplace(pair);
    }

    void append_map(parameter_t&& additional_params)
    {
        params.merge(std::move(additional_params));
    }
    void append_map(const parameter_t& additional_params)
    {
        params.insert(additional_params.begin(), additional_params.end());
    }

    template <typename _Attachment_List>
    void append_attachments(_Attachment_List&& attachments)
    {
        params.emplace("attachment", append_attachments_impl(std::forward<_Attachment_List>(attachments)).data());
    }

    parameter_t&& consume_map() noexcept
    {
        return std::move(params);
    }
    parameter_t map() const noexcept
    {
        return params;
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
    parameter_t params;
};
}// namespace method
}// namespace vk

#endif// VK_MESSAGE_CONSTRUCTOR_H
