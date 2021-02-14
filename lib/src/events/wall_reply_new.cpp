#include "simdjson.h"

#include "events/wall_reply_new.hpp"


vk::event::wall_reply_new::wall_reply_new(simdjson::dom::object&& event) {
    simdjson::dom::object wall_reply = event["object"];

    _id         = wall_reply["id"].get_int64();
    _from_id    = wall_reply["from_id"].get_int64();
    _post_id    = wall_reply["post_id"].get_int64();
    _owner_id   = wall_reply["owner_id"].get_int64();
    _text       = wall_reply["text"].get_string().take_value().data();

    if (wall_reply["attachments"].is_array())
        _attachments = att_handler.try_get(wall_reply["attachments"].get_array());
}

std::int64_t vk::event::wall_reply_new::id() const noexcept { return _id; }
std::int64_t vk::event::wall_reply_new::from_id() const noexcept { return _from_id; }
std::int64_t vk::event::wall_reply_new::post_id() const noexcept { return _post_id; }
std::int64_t vk::event::wall_reply_new::owner_id() const noexcept { return _owner_id; }
std::string  vk::event::wall_reply_new::text() const noexcept { return _text; }
vk::attachment::attachments_t vk::event::wall_reply_new::attachments() const noexcept { return _attachments; }
