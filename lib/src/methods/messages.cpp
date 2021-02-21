#include "simdjson.h"

#include "keyboard/layout.hpp"
#include "methods/messages.hpp"
#include "processing/error_handler.hpp"


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

vk::method::messages::messages()
  : parser(std::make_unique<simdjson::dom::parser>())
{ }

vk::method::messages::~messages() = default;

void vk::method::messages::send(std::int64_t peer_id, std::string_view text, const vk::attachment::attachments_t& list) {
  std::map<std::string, std::string> parameters;
  append_params(parameters, peer_id, text);
  append_attachments(parameters, list);
  method_util.call("messages.send", method_util.group_args(std::move(parameters)));
}

void vk::method::messages::send(std::int64_t peer_id, std::string_view text, std::map<std::string, std::string>&& raw_parameters) {
  auto parameters = raw_parameters;
  append_params(parameters, peer_id, text);
  method_util.call("messages.send", method_util.group_args(std::move(parameters)));
}

void vk::method::messages::send(int64_t peer_id, std::string_view text, const vk::keyboard::layout& layout) {
  std::map<std::string, std::string> parameters;
  append_params(parameters, peer_id, text);
  parameters.insert({{"keyboard", layout.serialize()}});
  method_util.call("messages.send", method_util.group_args(std::move(parameters)));
}

void vk::method::messages::send(std::int64_t peer_id, std::string_view text) {
  send(peer_id, text, vk::attachment::attachments_t());
}

void vk::method::messages::remove_chat_user(std::int64_t chat_id, std::int64_t user_id) {
  simdjson::dom::object parsed(
    method_util.call_and_parse("messages.removeChatUser", method_util.group_args({
      {"chat_id",    std::to_string(chat_id)},
      {"user_id",    std::to_string(user_id)},
      {"random_id",  "0"}
    }))
  );

  if (parsed.begin().key() == "response" && parsed["response"].get_int64() == 1)
    return;

  if (method_util.error_returned(parsed, 100)) {
    processing::process_error("messages", exception::access_error(1488, "Can't kick this user/group."));
  }

  if (method_util.error_returned(parsed, 15)) {
    processing::process_error("messages", exception::access_error(15, "Access denied."));
  }
}

void vk::method::messages::edit_chat(std::int64_t chat_id, std::string_view new_title) {
  method_util.call("messages.editChat", method_util.group_args({
    {"chat_id",     std::to_string(chat_id - method_util.chat_id_constant)},
    {"title",       new_title.data()},
    {"random_id",   "0"}
  }));
}

void vk::method::messages::delete_chat_photo(int64_t chat_id, int64_t group_id) {
  simdjson::dom::object response(
    method_util.call_and_parse("messages.deleteChatPhoto", method_util.group_args({
      {"chat_id",  std::to_string(chat_id - method_util.chat_id_constant)},
      {"group_id", std::to_string(group_id)}})
    )
  );

  if (method_util.error_returned(response, 15))
    processing::process_error("messages", exception::upload_error(15, "Can't delete chat photo. Maybe it already deleted?"));
}

void vk::method::messages::set_chat_photo(std::string_view filename, std::string_view raw_server) {
  simdjson::dom::object response(
    parser->parse(
      net_client.upload(
        "file",
        filename,
        parser->parse(raw_server)["response"]["upload_url"].get_string()
      )
    )
  );

  method_util.call("messages.setChatPhoto", method_util.group_args({
    {"file", response["response"].get_string().take_value().data()}
  }));
}

vk::conversation_member_list vk::method::messages::get_conversation_members(int64_t peer_id) {
  simdjson::dom::object response(
    method_util.call_and_parse(
      "messages.getConversationMembers",
      method_util.group_args({{"peer_id", std::to_string(peer_id)}})
    )
  );

  if (method_util.error_returned(response, 917))
    processing::process_error("messages", exception::access_error(917, "Access denied."));

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
