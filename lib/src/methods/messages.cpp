#include "methods/messages.hpp"

#include "exception/error_processor.hpp"
#include "keyboard/layout.hpp"
#include "methods/utility/message_constructor.hpp"
#include "simdjson.h"

vk::method::messages::messages(bool disable_mentions_flag)
  : m_disable_mentions_flag(disable_mentions_flag)
  , m_parser(std::make_shared<simdjson::dom::parser>())
  , m_document()
  , m_group_constructor()
  , m_user_constructor()
{}

vk::method::messages::~messages() = default;

void vk::method::messages::send(std::int64_t peer_id, std::string_view text, attachment::attachments_t list) const
{
    message_constructor constructor(m_disable_mentions_flag);

    constructor
        .param("peer_id", std::to_string(peer_id))
        .param("message", text)
        .attachments(std::move(list))
        .execute();
}

void vk::method::messages::send(std::int64_t peer_id, std::string_view text, std::map<std::string, std::string> raw_parameters) const
{
    message_constructor constructor(m_disable_mentions_flag);

    constructor
        .param("peer_id", std::to_string(peer_id))
        .param("message", text)
        .append_map(std::move(raw_parameters))
        .execute();
}

void vk::method::messages::send(int64_t peer_id, std::string_view text, std::string_view layout) const
{
    message_constructor constructor(m_disable_mentions_flag);

    constructor
        .param("peer_id", std::to_string(peer_id))
        .param("message", text)
        .param("keyboard", layout)
        .execute();
}

void vk::method::messages::send(std::int64_t peer_id, std::string_view text) const
{
    message_constructor constructor(m_disable_mentions_flag);

    constructor
        .param("peer_id", std::to_string(peer_id))
        .param("message", text)
        .execute();
}

void vk::method::messages::remove_chat_user(std::int64_t chat_id, std::int64_t user_id) const
{
    std::string raw_response = m_group_constructor
        .method("messages.removeChatUser")
        .param("chat_id", std::to_string(chat_id))
        .param("user_id", std::to_string(user_id))
        .param("random_id", "0")
        .execute();

    simdjson::dom::object response = m_parser->parse(raw_response);

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
    m_group_constructor
        .method("messages.editChat")
        .param("chat_id", std::to_string(chat_id - vk::method::utility::chat_id_constant))
        .param("title", new_title)
        .param("random_id", "0")
        .execute();
}

void vk::method::messages::create_chat(std::string_view title, std::int64_t group_id, std::vector<std::size_t> user_ids)
{
    m_group_constructor
        .method("messages.createChat")
        .param("title", title)
        .param("group_id", std::to_string(group_id))
        .param("user_ids", string_utils::join<std::size_t>(std::move(user_ids)))
        .execute();
}

void vk::method::messages::add_chat_user(int64_t chat_id, int64_t user_id)
{
    std::string raw_response = m_user_constructor
        .method("messages.addChatUser")
        .param("chat_id", std::to_string(chat_id - vk::method::utility::chat_id_constant))
        .param("user_id", std::to_string(user_id))
        .execute();

    simdjson::dom::object response = m_parser->parse(raw_response);

    if (response.begin().key() == "error")
    {
        processing::log_and_throw<exception::runtime_error>("messages", response);
    }
}

void vk::method::messages::delete_chat_photo(int64_t chat_id, int64_t group_id) const
{
    std::string raw_response = m_group_constructor
        .method("messages.deleteChatPhoto")
        .param("chat_id", std::to_string(chat_id - vk::method::utility::chat_id_constant))
        .param("group_id", std::to_string(group_id))
        .execute();

    simdjson::dom::object response = m_parser->parse(raw_response);

    if (response.begin().key() == "error")
    {
        processing::log_and_throw<exception::access_error>("messages", response);
    }
}

void vk::method::messages::pin(int64_t peer_id, int64_t message_id, std::int64_t conversation_message_id) const
{
    std::string raw_response = m_group_constructor
        .method("messages.pin")
        .param("peer_id", std::to_string(peer_id))
        .param("message_id", std::to_string(message_id))
        .param("conversation_message_id", std::to_string(conversation_message_id))
        .execute();

    simdjson::dom::object response = m_parser->parse(raw_response);

    if (response.begin().key() == "error")
    {
        processing::log_and_throw<exception::access_error>("messages", response);
    }
}

void vk::method::messages::set_chat_photo(std::string_view filename, std::string_view raw_server) const
{
    simdjson::dom::object response = m_document.upload(filename, raw_server, "file");
    m_group_constructor
        .method("messages.setChatPhoto")
        .param("file", response["response"])
        .execute();
}

vk::conversation_member_list vk::method::messages::get_conversation_members(int64_t peer_id) const
{
    std::string raw_response = m_group_constructor
        .method("messages.pin")
        .param("peer_id", std::to_string(peer_id))
        .execute();

    simdjson::dom::object response = m_parser->parse(raw_response);

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
