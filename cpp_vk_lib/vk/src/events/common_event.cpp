#include "vk/include/events/common_event.hpp"

#include "vk/include/events/message_new.hpp"
#include "vk/include/events/wall_post_new.hpp"
#include "vk/include/events/wall_reply_new.hpp"

#include "simdjson.h"

vk::event::common::~common() = default;

vk::event::common::common(std::string_view ts, simdjson::dom::object event)
    : m_ts(ts)
    , m_update_type()
    , m_event(std::make_shared<simdjson::dom::object>(event))
{
    m_update_type = (*m_event)["type"].get_string().take_value().data();
}

simdjson::dom::object& vk::event::common::get_event() const noexcept { return *m_event; }

bool vk::event::common::on_type(std::string_view type) const noexcept { return m_update_type == type; }

vk::event::common::operator message_new() const { return vk::event::message_new(std::move(get_event()["object"]["message"])); }
vk::event::common::operator wall_post_new() const { return vk::event::wall_post_new(std::move(get_event()["object"])); }
vk::event::common::operator wall_reply_new() const { return vk::event::wall_reply_new(std::move(get_event()["object"])); }

vk::event::message_new vk::event::common::get_message_new() const { return this->operator message_new(); }
vk::event::wall_post_new vk::event::common::get_wall_post_new() const { return this->operator wall_post_new(); }
vk::event::wall_reply_new vk::event::common::get_wall_reply_new() const { return this->operator wall_reply_new(); }

std::string vk::event::common::type() const noexcept { return m_update_type; }
std::string vk::event::common::ts() const noexcept { return m_ts; }
std::string vk::event::common::dump() const noexcept { return simdjson::to_string(get_event()); }
