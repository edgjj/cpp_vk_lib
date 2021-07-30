#include "vk/include/methods/utility/message_constructor.hpp"

vk::method::message_constructor::message_constructor(bool disable_mentions_flag)
{
    m_constructor.method("messages.send");

    param("random_id", "0");

    if (disable_mentions_flag) {
        param("disable_mentions", "1");
    } else {
        param("disable_mentions", "0");
    }
}

vk::method::message_constructor& vk::method::message_constructor::param(std::string_view lhs, std::string_view rhs)
{
    m_constructor.param(lhs, rhs);
    return *this;
}

vk::method::message_constructor& vk::method::message_constructor::append_map(std::map<std::string, std::string> additional_params)
{
    m_constructor.append_map(std::move(additional_params));
    return *this;
}

vk::method::message_constructor& vk::method::message_constructor::attachments(attachment::attachments_t attachments)
{
    param("attachment", append_attachments_impl(std::move(attachments)).data());
    return *this;
}

std::string vk::method::message_constructor::execute()
{
    return m_constructor.perform_request();
}

std::string vk::method::message_constructor::append_attachments_impl(attachment::attachments_t attachments) const
{
    std::string result;
    result.reserve(attachments.size() * 20);

    for (auto& attachment : attachments) {
        result += attachment->value();
        result += ',';
    }

    return result;
}

