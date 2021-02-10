#include "simdjson.h"

#include "events/wall_post_new.hpp"


vk::event::wall_post_new::wall_post_new(std::string_view raw_json) {
    static simdjson::dom::parser parser;
    static simdjson::dom::object response = parser.parse(raw_json)["object"];

    _id      = response["id"].get_int64();
    _from_id = response["from_id"].get_int64();
}
std::int64_t vk::event::wall_post_new::from_id() const noexcept {
    return _from_id;
}
std::int64_t vk::event::wall_post_new::id() const noexcept {
    return _id;
}
