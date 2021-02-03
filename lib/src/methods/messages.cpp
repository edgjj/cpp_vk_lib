#include <simdjson.h>

#include "lib/include/utility/exception.hpp"
#include "lib/include/net/network_client.hpp"
#include "lib/include/methods/messages.hpp"


static void append_attachments(std::map<std::string, std::string>& parameters, const vk::attachment::attachments_t& list)
{
    std::string attachments;
    for (auto&& attachment : list)
    {
        attachments += attachment->value() + ',';
    }
    parameters.insert({{"attachment", attachments}});
}

void vk::messages::send(std::int64_t peer_id, std::string_view text, const vk::attachment::attachments_t& list)
{
    std::map<std::string, std::string> parameters =
    group_params({
        {"random_id",    "0"        },
        {"message",      text.data()},
        {"peer_id",      std::to_string(peer_id) },
        {"disable_mentions", "1"    },
    });

    if (!list.empty())
    {
        append_attachments(parameters, list);
    }
    call("messages.send", parameters);
}

void vk::messages::send(std::int64_t peer_id, std::string_view text)
{
    send(peer_id, text, {});
}

void vk::messages::remove_chat_user(std::int64_t chat_id, std::int64_t user_id)
{
    std::string response =
    call("messages.removeChatUser", group_params({
        {"chat_id",      std::to_string(chat_id)},
        {"user_id",      std::to_string(user_id)},
        {"random_id",    "0"}
    }));

    simdjson::dom::object parsed = parser.parse(response);

    if (parsed.begin().key() == "response" && static_cast<long>(parsed["response"]) == 1)
    {
        return;
    }
    if (!parsed["error"].is_null() && static_cast<std::int64_t>(parsed["error"]["error_code"]) == 100)
    {
        VK_THROW(exception::access_error, 100, "Can't kick this user/group.");
    }
    if (!parsed["error"].is_null() && static_cast<std::int64_t>(parsed["error"]["error_code"]) == 15)
    {
        VK_THROW(exception::access_error, 15, "Access denied.");
    }
}

void vk::messages::edit_chat(std::int64_t chat_id, std::string_view new_title)
{
    call("messages.editChat", group_params({
        {"chat_id",   std::to_string(chat_id - 2000000000)},
        {"title",     new_title.data()},
        {"random_id", "0"}
    }));
}

void vk::messages::set_chat_photo(std::string_view filename, std::string_view raw_server)
{
    simdjson::dom::object response =
    parser.parse(
        network_client.upload(
            "file",
            filename,
            static_cast<std::string>(parser.parse(raw_server)["response"]["upload_url"])
        )
    );

    std::string raw_vk_response =
    call("messages.setChatPhoto", group_params({
        {"file", static_cast<std::string>(response["response"])}
    }));
}

vk::conversation_member_list vk::messages::get_conversation_members(int64_t peer_id)
{
    simdjson::dom::object response =
    parser.parse(
        call(
            "messages.getConversationMembers",
            group_params({{"peer_id", std::to_string(peer_id)}})
        )
    );

    if (response.begin().key() == "error" && response["error"]["error_code"].get_int64() == 917L)
    {
        VK_THROW(exception::access_error, 917, "Access denied.");
    }

    conversation_member_list members;
    for (auto&& profile : response["response"]["profiles"].get_array())
    {
        members.push_back({
            static_cast<std::string_view>(profile["first_name"]).data(),
            static_cast<std::string_view>(profile["last_name"]).data(),
            static_cast<std::int64_t>(profile["id"]),
           (static_cast<std::int64_t>(profile["online"]) == 1) ? true : false
        });
    }

    return members;
}
