#include "simdjson.h"

#include "events/wall_reply_new.hpp"
#include "processing/process_error.hpp"


vk::event::wall_reply_new::wall_reply_new(simdjson::dom::object&& event)
  : _event_json(std::make_shared<simdjson::dom::object>(event))
{
  if (event["attachments"].is_array() && event["attachments"].get_array().size() > 0)
    _has_attachments = true;
}

std::int64_t vk::event::wall_reply_new::id() const noexcept {
  return (*_event_json)["id"].get_int64();
}
std::int64_t vk::event::wall_reply_new::from_id() const noexcept {
  return (*_event_json)["from_id"].get_int64();
}
std::int64_t vk::event::wall_reply_new::post_id() const noexcept {
  return (*_event_json)["post_id"].get_int64();
}
std::int64_t vk::event::wall_reply_new::owner_id() const noexcept {
  return (*_event_json)["owner_id"].get_int64();
}
std::string  vk::event::wall_reply_new::text() const noexcept {
  return (*_event_json)["text"].get_c_str().take_value();
}
vk::attachment::attachments_t vk::event::wall_reply_new::attachments() const {
  if (_has_attachments) {
    return att_handler.try_get((*_event_json)["attachments"].get_array());
  } else {
    // Exception thrown there, hence final return will never executed.
    processing::process_error("wall_reply_new", exception::access_error(
      -1, "Attempting accessing empty attachment list"));
  }
  return { };
}
