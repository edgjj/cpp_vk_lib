#include "simdjson.h"

#include "events/wall_post_new.hpp"
#include "processing/process_error.hpp"


vk::event::wall_post_new::wall_post_new(simdjson::dom::object&& event)
  : _event_json(std::make_shared<simdjson::dom::object>(event))
{
if (event["attachments"].is_array())
  _has_attachments = true;

if (event["copy_history"].is_array())
  _has_repost = true;
}

std::int64_t vk::event::wall_post_new::id() const noexcept {
  return (*_event_json)["id"].get_int64();
}
std::int64_t vk::event::wall_post_new::from_id() const noexcept {
  return (*_event_json)["from_id"].get_int64();
}
std::int64_t vk::event::wall_post_new::owner_id() const noexcept {
  return (*_event_json)["owner_id"].get_int64();
}
std::int64_t vk::event::wall_post_new::created_by() const noexcept {
  return (*_event_json)["created_by"].get_int64();
}
std::string  vk::event::wall_post_new::text() const noexcept {
  return (*_event_json)["text"].get_string().take_value().data();
}
bool vk::event::wall_post_new::can_edit() const noexcept {
  return (*_event_json)["can_edit"].get_int64();
}
bool vk::event::wall_post_new::can_delete() const noexcept {
  return (*_event_json)["can_delete"].get_int64();
}
bool vk::event::wall_post_new::marked_as_ads() const noexcept {
  return (*_event_json)["marked_as_ads"].get_int64();
}
vk::attachment::attachments_t vk::event::wall_post_new::attachments() const noexcept {
  if (vk_likely(_has_attachments)) {
    return _attachment_handler.try_get((*_event_json)["attachments"].get_array());
  } else {
    // Exception thrown there, hence final return will never executed.
    processing::process_error("wall_post_new", exception::access_error(
      -1, "Attempting accessing empty attachment list."));
  }
  return { };
}
std::shared_ptr<vk::event::wall_repost> vk::event::wall_post_new::repost() const {
  simdjson::dom::object repost_json = (*_event_json)["copy_history"].get_array().at(0).get_object();

  if (vk_likely(_has_repost)) {
    std::shared_ptr<wall_repost> repost =
      std::make_shared<wall_repost>(
        repost_json["id"].get_int64(),
        repost_json["from_id"].get_int64(),
        repost_json["owner_id"].get_int64(),
        repost_json["text"].get_c_str().take_value()
      );
    if (repost_json["attachments"].is_array() && repost_json["attachments"].get_array().size() > 0) {
      repost->construct_attachments(
        _attachment_handler.try_get(repost_json["attachments"].get_array()));
    }
    return repost;
  } else {
    // Exception thrown there, hence final return will never executed.
    processing::process_error("wall_post_new", exception::access_error(
      -1, "Attempting accessing empty repost."));
  }
  return { };
}
