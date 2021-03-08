#include "simdjson.h"

#include "events/wall_reply_new.hpp"
#include "exception/error_processor.hpp"


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
bool vk::event::wall_reply_new::has_attachments() const noexcept {
  return _has_attachments;
}
vk::attachment::attachments_t vk::event::wall_reply_new::attachments() const {
  if (_has_attachments) {
    return att_handler.try_get((*_event_json)["attachments"].get_array());
  } else {
    // Exception thrown there, hence final return will never executed.
    processing::log_and_throw(
      "wall_reply_new", processing::error_type::access_error, "Attempting accessing empty attachment list"
    );
  }
  return { };
}

std::ostream& operator<<(std::ostream& ostream, const vk::event::wall_reply_new& reply) {
  ostream << "wall_reply_new:" << std::endl;
  ostream << "  " << "id:               " << reply.id() << std::endl;
  ostream << "  " << "from_id:          " << reply.from_id() << std::endl;
  ostream << "  " << "post_id:          " << reply.post_id() << std::endl;
  ostream << "  " << "owner_id:         " << reply.owner_id() << std::endl;
  ostream << "  " << "text:             " << reply.text() << std::endl;
  ostream << "  " << "has_attachments?  " << reply.has_attachments() << std::endl;
  if (reply.has_attachments()) {
    for (auto& attachment : reply.attachments()) {
      ostream << "    " << "attachment:       ";
      ostream << attachment->value();
      ostream << std::endl;
    }
  }
  return ostream;
}
