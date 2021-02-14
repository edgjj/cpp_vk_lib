#include "simdjson.h"

#include "processing/exception.hpp"
#include "events/wall_post_new.hpp"


void vk::event::wall_post_new::construct(const simdjson::dom::object& event, bool is_reply)
{
  _id             = event["id"].get_int64();
  _from_id        = event["from_id"].get_int64();
  _owner_id       = event["owner_id"].get_int64();
  _text           = event["text"].get_string().take_value().data();
  if (!is_reply) {
    _created_by     = event["created_by"].get_int64();
    _can_edit       = event["can_edit"].get_int64();
    _can_delete     = event["can_delete"].get_int64();
    _marked_as_ads  = event["marked_as_ads"].get_int64();
  }
}

vk::event::wall_post_new::wall_post_new(const simdjson::dom::object& event) {
  construct(event, is_reply);
}

vk::event::wall_post_new::wall_post_new(simdjson::dom::object&& event) {
  simdjson::dom::object wall_post_event = event["object"];
  construct(wall_post_event, is_not_reply);

  if (wall_post_event["attachments"].is_array())
    _attachments = _attachment_handler.try_get(wall_post_event["attachments"].get_array());

  if (wall_post_event["copy_history"].is_array())
    _repost = std::make_shared<wall_post_new>(wall_post_new(wall_post_event["copy_history"].get_array().at(0).get_object()));
}

std::int64_t vk::event::wall_post_new::id()         const noexcept { return _id; }
std::int64_t vk::event::wall_post_new::from_id()    const noexcept { return _from_id; }
int64_t      vk::event::wall_post_new::owner_id()   const noexcept { return _owner_id; }
int64_t      vk::event::wall_post_new::created_by() const noexcept { return _created_by; }
std::string  vk::event::wall_post_new::text()       const noexcept { return _text; }
bool vk::event::wall_post_new::can_edit()           const noexcept { return _can_edit; }
bool vk::event::wall_post_new::can_delete()         const noexcept { return _can_delete; }
bool vk::event::wall_post_new::marked_as_ads()      const noexcept { return _marked_as_ads; }
vk::attachment::attachments_t vk::event::wall_post_new::attachments() const noexcept { return _attachments; }

std::shared_ptr<vk::event::wall_post_new> vk::event::wall_post_new::repost() const {
    if (vk_likely(_repost)) return _repost;
    else vk_throw(vk::exception::access_error, -1, "Attempting accessing empty repost.");
}
