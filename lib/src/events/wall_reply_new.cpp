#include "simdjson.h"

#include "events/wall_reply_new.hpp"


vk::event::wall_reply_new::wall_reply_new(std::string_view raw_json) {
    simdjson::dom::parser parser;
    simdjson::dom::object event = parser.parse(raw_json)["object"];

    _id         = event["id"].get_int64();
    _from_id    = event["from_id"].get_int64();
    _post_id    = event["post_id"].get_int64();
    _owner_id   = event["owner_id"].get_int64();
    _text       = event["text"].get_string().take_value().data();

    if (event["attachments"].is_array())
        _attachments = att_handler.try_get(event["attachments"].get_array());
}

std::int32_t vk::event::wall_reply_new::id() const noexcept { return _id; }
std::int64_t vk::event::wall_reply_new::from_id() const noexcept { return _from_id; }
std::int32_t vk::event::wall_reply_new::post_id() const noexcept { return _post_id; }
std::int64_t vk::event::wall_reply_new::owner_id() const noexcept { return _owner_id; }
std::string  vk::event::wall_reply_new::text() const noexcept { return _text; }
vk::attachment::attachments_t vk::event::wall_reply_new::attachments() const noexcept { return _attachments; }
