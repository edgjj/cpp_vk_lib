#include "simdjson.h"

#include "processing/exception.hpp"
#include "events/message_new.hpp"
#include "../dependencies/logger/logger.hpp"


vk::event::message_new::message_new(simdjson::dom::object&& event) {
  _message_json = std::make_shared<simdjson::dom::object>(event);

  if (event["reply_message"].is_object())
    _has_reply = true;

  if (event["attachments"].is_array())
    _has_attachments = true;

  if (event["fwd_messages"].is_array() && event["fwd_messages"].get_array().size() != 0)
    _has_fwd_messages = true;

  if (event["action"].is_object())
    _has_action = true;
}

void vk::event::message_new::try_get_actions() {
  simdjson::dom::object action_object = (*_message_json)["action"].get_object();
  std::string action_name = action_object["type"].get_string().take_value().data();
  if (action_name == "chat_invite_user") {
    _action = std::make_shared<action::chat_invite_user>(
      action_object["member_id"].get_int64()
    );
  }
  if (action_name == "chat_kick_user") {
    _action = std::make_shared<action::chat_kick_user>(
      action_object["member_id"].get_int64()
    );
  }
  if (action_name == "chat_pin_message") {
    _action = std::make_shared<action::chat_pin_message>(
      action_object["member_id"].get_int64(),
      action_object["conversation_message_id"].get_int64(),
      action_object["message"].get_string()
    );
  }
  if (action_name == "chat_unpin_message") {
    _action = std::make_shared<action::chat_unpin_message>(
      action_object["member_id"].get_int64(),
      action_object["conversation_message_id"].get_int64()
    );
  }
  if (action_name == "chat_photo_update") {
    _action = std::make_shared<action::chat_photo_update>(
      // empty
    );
  }
  if (action_name == "chat_title_update") {
    _action = std::make_shared<action::chat_title_update>(
      action_object["text"].get_string()
    );
  }
}

bool vk::event::message_new::on_action(std::string_view action_name) const noexcept {
  if (action_name == "chat_invite_user")   { return std::holds_alternative<action::chat_invite_user_ptr>(_action); }
  if (action_name == "chat_kick_user")     { return std::holds_alternative<action::chat_kick_user_ptr>(_action); }
  if (action_name == "chat_pin_message")   { return std::holds_alternative<action::chat_pin_message_ptr>(_action); }
  if (action_name == "chat_unpin_message") { return std::holds_alternative<action::chat_unpin_message_ptr>(_action); }
  if (action_name == "chat_photo_update")  { return std::holds_alternative<action::chat_photo_update_ptr>(_action); }
  if (action_name == "chat_title_update")  { return std::holds_alternative<action::chat_title_update_ptr>(_action); }
  return false;
}

std::int64_t vk::event::message_new::conversation_message_id() const noexcept {
  return (*_message_json)["conversation_message_id"].get_int64();
}
std::int64_t vk::event::message_new::peer_id() const noexcept {
  return (*_message_json)["peer_id"].get_int64();
}
std::int64_t vk::event::message_new::from_id() const noexcept {
  return (*_message_json)["from_id"].get_int64();
}
std::string vk::event::message_new::text() const noexcept {
  return (*_message_json)["text"].get_c_str().take_value();
}
bool vk::event::message_new::has_action() const noexcept {
  return _has_action;
}
bool vk::event::message_new::has_reply() const noexcept {
  return _has_reply;
}
bool vk::event::message_new::has_fwd_messages() const noexcept {
  return _has_fwd_messages;
}
vk::action::any_action vk::event::message_new::action() {
  if (_has_action) {
    try_get_actions();
    return std::move(_action);
  } else {
    vk_throw(exception::access_error, -1, "Attempting accessing empty action.");
  }
}
vk::attachment::attachments_t vk::event::message_new::attachments() const {
  if (_has_attachments) {
    return att_handler.try_get((*_message_json)["attachments"].get_array());
  } else {
    vk_throw(exception::access_error, -1, "Attempting accessing empty attachment list");
  }
}
std::vector<std::unique_ptr<vk::event::message_new>> vk::event::message_new::fwd_messages() const {
  if (_has_fwd_messages) {
    std::vector<std::unique_ptr<message_new>> fwd_messages;
    for (simdjson::dom::element&& fwd_message : (*_message_json)["fwd_messages"].get_array()) {
      fwd_messages.push_back(
        std::make_unique<message_new>(fwd_message)
      );
    }
    return fwd_messages;
  } else {
    vk_throw(exception::access_error, -1, "Attempting accessing empty forward message list.");
  }
}
std::shared_ptr<vk::event::message_new> vk::event::message_new::reply() {
  if (_has_reply) {
    return std::make_unique<message_new>((*_message_json)["reply_message"].get_object());
  } else {
    vk_throw(exception::access_error, -1, "Attempting accessing empty reply.");
  }
}
