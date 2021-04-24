#include "methods/messages.hpp"

#include "exception/error_processor.hpp"
#include "keyboard/layout.hpp"
#include "methods/utility/message_constructor.hpp"
#include "simdjson.h"

vk::method::messages::messages(bool disable_mentions_flag_)
  : m_disable_mentions_flag(disable_mentions_flag_)
  , m_parser(std::make_shared<simdjson::dom::parser>())
  , m_document()
  , m_method_util()
{}

vk::method::messages::~messages() = default;

template <typename _Attachment_Container>
static auto
construct_with_attachments_impl(bool disable_mentions_flag, std::int64_t peer_id, std::string_view text, _Attachment_Container&& list)
{
    vk::method::message_constructor constructor(disable_mentions_flag);
    constructor.append({"peer_id", std::to_string(peer_id)});
    constructor.append({"message", text.data()});
    constructor.append_attachments(std::forward<_Attachment_Container>(list));
    return constructor;
}

template <typename _Map_Container>
static auto
construct_with_raw_parameters_impl(bool disable_mentions_flag, std::int64_t peer_id, std::string_view text, _Map_Container&& list)
{
    vk::method::message_constructor constructor(disable_mentions_flag);
    constructor.append({"peer_id", std::to_string(peer_id)});
    constructor.append({"message", text.data()});
    constructor.append_map(std::forward<_Map_Container>(list));
    return constructor;
}

void vk::method::messages::send(std::int64_t peer_id, std::string_view text, attachment::attachments_t&& list) const
{
    auto constructed_message = construct_with_attachments_impl(disable_mentions, peer_id, text, std::move(list));
    m_method_util.call("messages.send", m_method_util.group_args(constructed_message.consume_map()));
}

void vk::method::messages::send(std::int64_t peer_id, std::string_view text, const attachment::attachments_t& list) const
{
    auto constructed_message = construct_with_attachments_impl(disable_mentions, peer_id, text, list);
    m_method_util.call("messages.send", m_method_util.group_args(constructed_message.consume_map()));
}

void vk::method::messages::send(std::int64_t peer_id, std::string_view text, std::map<std::string, std::string>&& raw_parameters) const
{
    auto constructed_message = construct_with_raw_parameters_impl(disable_mentions, peer_id, text, std::move(raw_parameters));
    m_method_util.call("messages.send", m_method_util.group_args(constructed_message.consume_map()));
}

void vk::method::messages::send(std::int64_t peer_id, std::string_view text, const std::map<std::string, std::string>& raw_parameters) const
{
    auto constructed_message = construct_with_raw_parameters_impl(disable_mentions, peer_id, text, raw_parameters);
    m_method_util.call("messages.send", m_method_util.group_args(constructed_message.consume_map()));
}

void vk::method::messages::send(int64_t peer_id, std::string_view text, std::string_view layout) const
{
    message_constructor constructor(m_disable_mentions_flag);
    constructor.append({"peer_id", std::to_string(peer_id)});
    constructor.append({"message", text.data()});
    constructor.append({"keyboard", layout.data()});
    m_method_util.call("messages.send", m_method_util.group_args(constructor.consume_map()));
}

void vk::method::messages::send(std::int64_t peer_id, std::string_view text) const
{
    message_constructor constructor(m_disable_mentions_flag);
    constructor.append({"peer_id", std::to_string(peer_id)});
    constructor.append({"message", text.data()});
    m_method_util.call("messages.send", m_method_util.group_args(constructor.consume_map()));
}

void vk::method::messages::remove_chat_user(std::int64_t chat_id, std::int64_t user_id) const
{
    simdjson::dom::object response = m_method_util.call_and_parse(
        "messages.removeChatUser",
        m_method_util.group_args({{"chat_id", std::to_string(chat_id)}, {"user_id", std::to_string(user_id)}, {"random_id", "0"}}));

    if (response.begin().key() == "response" && response["response"].get_int64() == 1)
    {
        return;
    }
    if (response.begin().key() == "error")
    {
        processing::log_and_throw<exception::access_error>("messages", response);
    }
}

void vk::method::messages::edit_chat(std::int64_t chat_id, std::string_view new_title) const
{
    m_method_util.call(
        "messages.editChat",
        m_method_util.group_args(
            {{"chat_id", std::to_string(chat_id - m_method_util.chat_id_constant)}, {"title", new_title.data()}, {"random_id", "0"}}));
}

void vk::method::messages::delete_chat_photo(int64_t chat_id, int64_t group_id) const
{
    simdjson::dom::object response = m_method_util.call_and_parse(
        "messages.deleteChatPhoto",
        m_method_util.group_args(
            {{"chat_id", std::to_string(chat_id - m_method_util.chat_id_constant)}, {"group_id", std::to_string(group_id)}}));

    if (response.begin().key() == "error")
    {
        processing::log_and_throw<exception::access_error>("messages", response);
    }
}

void vk::method::messages::pin(int64_t peer_id, int64_t message_id, std::int64_t conversation_message_id) const
{
    simdjson::dom::object response = m_method_util.call_and_parse(
        "messages.pin",
        m_method_util.group_args(
            {{"peer_id", std::to_string(peer_id)},
             {"message_id", std::to_string(message_id)},
             {"conversation_message_id", std::to_string(conversation_message_id)}}));

    if (response.begin().key() == "error")
    {
        processing::log_and_throw<exception::access_error>("messages", response);
    }
}

void vk::method::messages::set_chat_photo(std::string_view filename, std::string_view raw_server) const
{
    simdjson::dom::object response = m_document.upload(filename, raw_server, "file");
    m_method_util.call("messages.setChatPhoto", m_method_util.group_args({{"file", response["response"].get_c_str().take_value()}}));
}

vk::conversation_member_list vk::method::messages::get_conversation_members(int64_t peer_id) const
{
    simdjson::dom::object response =
        m_method_util.call_and_parse("messages.getConversationMembers", m_method_util.group_args({{"peer_id", std::to_string(peer_id)}}));

    if (response.begin().key() == "error")
    {
        processing::log_and_throw<exception::access_error>("messages", response);
    }

    conversation_member_list members;
    for (auto&& profile : response["response"]["profiles"].get_array())
    {
        members.push_back(
            {profile["first_name"].get_string().take_value().data(),
             profile["last_name"].get_string().take_value().data(),
             profile["id"].get_int64(),
             (profile["online"].get_int64() == 1) ? true : false});
    }

    return members;
}
