#include "simdjson.h"

#include "events/common_event.hpp"


vk::event::common::~common() = default;

vk::event::common::common(std::string_view ts, simdjson::dom::object&& event)
  : _ts(ts), _update_type(), _event(std::make_unique<simdjson::dom::object>(event))
{
  _update_type = event["type"].get_string().take_value().data();
}

bool vk::event::common::on_type(std::string_view type) const noexcept {
  return _update_type == type;
}
vk::event::message_new vk::event::common::get_message_event() const {
  return vk::event::message_new(std::move(*_event)["object"]["message"]);
}
vk::event::wall_post_new vk::event::common::get_wall_post_event() const {
  return vk::event::wall_post_new(std::move(*_event)["object"]);
}
vk::event::wall_reply_new vk::event::common::get_wall_reply_event() const {
  return vk::event::wall_reply_new(std::move(*_event)["object"]);
}
std::string vk::event::common::type() const noexcept {
  return _update_type;
}
std::string vk::event::common::ts() const noexcept {
  return _ts;
}
std::string vk::event::common::dump() const noexcept {
  return simdjson::to_string(*_event);
}
