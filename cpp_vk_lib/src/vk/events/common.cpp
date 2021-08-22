#include "cpp_vk_lib/vk/events/common.hpp"

#include "cpp_vk_lib/vk/events/message_new.hpp"
#include "cpp_vk_lib/vk/events/wall_post_new.hpp"
#include "cpp_vk_lib/vk/events/wall_reply_new.hpp"
#include "simdjson.h"

namespace vk::event {

common::~common() = default;

common::common(std::string_view ts, simdjson::dom::object event)
    : ts_(ts)
    , update_type_()
    , event_(std::make_shared<simdjson::dom::object>(event))
{
    update_type_ = (*event_)["type"].get_string().take_value().data();
}

simdjson::dom::object& common::get_event() const noexcept
{
    return *event_;
}

bool common::on_type(std::string_view type) const noexcept
{
    return update_type_ == type;
}

common::operator message_new() const
{
    return message_new(std::move(get_event()["object"]["message"]));
}

common::operator wall_post_new() const
{
    return wall_post_new(std::move(get_event()["object"]));
}

common::operator wall_reply_new() const
{
    return wall_reply_new(std::move(get_event()["object"]));
}

message_new common::get_message_new() const
{
    return this->operator message_new();
}

wall_post_new common::get_wall_post_new() const
{
    return this->operator wall_post_new();
}

wall_reply_new common::get_wall_reply_new() const
{
    return this->operator wall_reply_new();
}

std::string common::type() const noexcept
{
    return update_type_;
}

std::string common::ts() const noexcept
{
    return ts_;
}

std::string common::dump() const noexcept
{
    return simdjson::to_string(get_event());
}

}// namespace vk::event
