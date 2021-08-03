#include "vk/include/events/wall_reply_new.hpp"

#include "vk/include/events/handlers/attachment_handler.hpp"
#include "vk/include/exception/error-inl.hpp"

#include "runtime/include/misc/cppdefs.hpp"

#include "simdjson.h"
#include "spdlog/spdlog.h"

vk::event::wall_reply_new::~wall_reply_new() = default;

vk::event::wall_reply_new::wall_reply_new(simdjson::dom::object&& event)
    : m_event_json(std::make_shared<simdjson::dom::object>(std::move(event)))
{
    if (get_event()["attachments"].is_array() && get_event()["attachments"].get_array().size() > 0) {
        m_has_attachments = true;
    }

    spdlog::info("create wall_reply_new");
    spdlog::info("\thas attachments? {}", m_has_attachments);
}

simdjson::dom::object& vk::event::wall_reply_new::get_event() const
{
    return *m_event_json;
}

int64_t vk::event::wall_reply_new::id() const noexcept
{
    return get_event()["id"].get_int64();
}

int64_t vk::event::wall_reply_new::from_id() const noexcept
{
    return get_event()["from_id"].get_int64();
}

int64_t vk::event::wall_reply_new::post_id() const noexcept
{
    return get_event()["post_id"].get_int64();
}

int64_t vk::event::wall_reply_new::owner_id() const noexcept
{
    return get_event()["owner_id"].get_int64();
}

std::string vk::event::wall_reply_new::text() const noexcept
{
    return get_event()["text"].get_c_str().take_value();
}

bool vk::event::wall_reply_new::has_attachments() const noexcept
{
    return m_has_attachments;
}

std::vector<vk::attachment::attachment_ptr_t> vk::event::wall_reply_new::attachments() const
{
    if (m_has_attachments) {
        return event::get_attachments(get_event()["attachments"].get_array());
    } else {
        throw exception::access_error(-1, "Attempting accessing empty attachment list");
    }
}

std::ostream& operator<<(std::ostream& ostream, const vk::event::wall_reply_new& reply)
{
    ostream << "wall_reply_new:" << std::endl;

    ostream << std::setw(30)
            << "id: " << reply.id() << std::endl;
    ostream << std::setw(30)
            << "from_id: " << reply.from_id() << std::endl;
    ostream << std::setw(30)
            << "post_id: " << reply.post_id() << std::endl;
    ostream << std::setw(30)
            << "owner_id: " << reply.owner_id() << std::endl;
    ostream << std::setw(30)
            << "text: " << reply.text() << std::endl;
    ostream << std::setw(30)
            << "has_attachments? " << reply.has_attachments() << std::endl;

    if (reply.has_attachments()) {
        for (auto& attachment : reply.attachments()) {
            ostream << std::setw(40)
                    << "attachment: ";
            ostream << attachment->value();
            ostream << std::endl;
        }
    }

    return ostream;
}
