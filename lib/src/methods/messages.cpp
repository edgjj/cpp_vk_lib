#include <numeric>

#include "processing/exception.hpp"
#include "methods/messages.hpp"


static inline void append_params(std::map<std::string, std::string>& parameters, std::int64_t peer_id, std::string_view text) {
    parameters.insert(
        {{"random_id","0"}, {"disable_mentions","1"},
        {"peer_id",std::to_string(peer_id)}, {"message",text.data()}}
    );
}

static inline void append_attachments(std::map<std::string, std::string>& parameters, const vk::attachment::attachments_t& list) {
    auto lambda = [](std::string& res, std::shared_ptr<vk::attachment::base_attachment> att) mutable {
        return res += att->value() + ',';
    };
    parameters.insert({{
        "attachment", std::accumulate(list.begin(), list.end(), std::string(), lambda)
    }});
}

void vk::messages::send(std::int64_t peer_id, std::string_view text, const vk::attachment::attachments_t& list) {
    std::map<std::string, std::string> parameters;
    append_params(parameters, peer_id, text);
    append_attachments(parameters, list);
    call("messages.send", group_args(std::move(parameters)));
}

void vk::messages::send(std::int64_t peer_id, std::string_view text, std::map<std::string, std::string>&& raw_parameters) {
    auto parameters = raw_parameters;
    append_params(parameters, peer_id, text);
    call("messages.send", group_args(std::move(parameters)));
}

void vk::messages::send(std::int64_t peer_id, std::string_view text) {
    send(peer_id, text, vk::attachment::attachments_t());
}

void vk::messages::remove_chat_user(std::int64_t chat_id, std::int64_t user_id) {
    simdjson::dom::object parsed(
        call_and_parse("messages.removeChatUser", group_args({
            {"chat_id",      std::to_string(chat_id)},
            {"user_id",      std::to_string(user_id)},
            {"random_id",    "0"}
        }))
    );

    if (parsed.begin().key() == "response" && parsed["response"].get_int64() == 1)
        return;

    if (error_returned(parsed, 100))
        VK_THROW(exception::access_error, 100, "Can't kick this user/group.");

    if (error_returned(parsed, 15))
        VK_THROW(exception::access_error, 15, "Access denied.");
}

void vk::messages::edit_chat(std::int64_t chat_id, std::string_view new_title) {
    call("messages.editChat", group_args({
        {"chat_id",   std::to_string(chat_id - chat_id_constant)},
        {"title",     new_title.data()},
        {"random_id", "0"}
    }));
}

void vk::messages::delete_chat_photo(int64_t chat_id, int64_t group_id) {
    simdjson::dom::object response(
        call_and_parse("messages.deleteChatPhoto", group_args({
            {"chat_id",  std::to_string(chat_id - chat_id_constant)},
            {"group_id", std::to_string(group_id)}})
        )
    );

    if (error_returned(response, 15))
        VK_THROW(vk::exception::upload_error, 15, "Can't delete chat photo. Maybe it already deleted?");
}

void vk::messages::set_chat_photo(std::string_view filename, std::string_view raw_server) {
    simdjson::dom::object response(
        parser.parse(
            net_client.upload(
                "file",
                filename,
                parser.parse(raw_server)["response"]["upload_url"].get_string()
            )
        )
    );

    call("messages.setChatPhoto", group_args({
        {"file", response["response"].get_string().take_value().data()}
    }));
}

vk::conversation_member_list vk::messages::get_conversation_members(int64_t peer_id) {
    simdjson::dom::object response(
        call_and_parse(
            "messages.getConversationMembers",
            group_args({{"peer_id", std::to_string(peer_id)}})
        )
    );

    if (error_returned(response, 917))
        VK_THROW(exception::access_error, 917, "Access denied.");

    conversation_member_list members;
    for (auto&& profile : response["response"]["profiles"].get_array()) {
        members.push_back({
            profile["first_name"].get_string().take_value().data(),
            profile["last_name"].get_string().take_value().data(),
            profile["id"].get_int64(),
           (profile["online"].get_int64() == 1) ? true : false
        });
    }

    return members;
}
