#include "vk/include/events/wall_post_new.hpp"

#include "vk/include/events/handlers/attachment_handler.hpp"
#include "vk/include/exception/error-inl.hpp"

#include "runtime/include/misc/cppdefs.hpp"

#include "simdjson.h"
#include "spdlog/spdlog.h"

vk::event::wall_post_new::~wall_post_new() = default;

vk::event::wall_post_new::wall_post_new(simdjson::dom::object&& event)
    : m_event_json(std::make_shared<simdjson::dom::object>(std::move(event)))
{
    if (get_event()["attachments"].is_array()) {
        m_has_attachments = true;
    }

    if (get_event()["copy_history"].is_array()) {
        m_has_repost = true;
    }

    spdlog::info("create wall_post_new");
    spdlog::info("\thas attachments? {}", m_has_attachments);
    spdlog::info("\thas repost?      {}", m_has_repost);
}

int64_t vk::event::wall_post_new::id() const noexcept
{
    return get_event()["id"].get_int64();
}

int64_t vk::event::wall_post_new::from_id() const noexcept
{
    return get_event()["from_id"].get_int64();
}

int64_t vk::event::wall_post_new::owner_id() const noexcept
{
    return get_event()["owner_id"].get_int64();
}

int64_t vk::event::wall_post_new::created_by() const noexcept
{
    return get_event()["created_by"].get_int64();
}

std::string vk::event::wall_post_new::text() const noexcept
{
    return get_event()["text"].get_string().take_value().data();
}

bool vk::event::wall_post_new::can_edit() const noexcept
{
    return get_event()["can_edit"].get_int64();
}

bool vk::event::wall_post_new::can_delete() const noexcept
{
    return get_event()["can_delete"].get_int64();
}

bool vk::event::wall_post_new::marked_as_ads() const noexcept
{
    return get_event()["marked_as_ads"].get_int64();
}

bool vk::event::wall_post_new::has_attachments() const noexcept
{
    return m_has_attachments;
}

bool vk::event::wall_post_new::has_repost() const noexcept
{
    return m_has_repost;
}

simdjson::dom::object& vk::event::wall_post_new::get_event() const
{
    return *m_event_json;
}

std::vector<vk::attachment::attachment_ptr_t> vk::event::wall_post_new::attachments() const
{
    if (m_has_attachments) {
        return event::get_attachments(get_event()["attachments"].get_array());
    } else {
        throw exception::access_error(-1 ,"Attempting accessing empty attachment list.");
    }
}

std::shared_ptr<vk::event::wall_repost> vk::event::wall_post_new::repost() const
{
    simdjson::dom::object repost_json = get_event()["copy_history"].get_array().at(0).get_object();

    if (m_has_repost) {
        std::shared_ptr<wall_repost> repost = std::make_shared<wall_repost>(
            repost_json["id"].get_int64(),
            repost_json["from_id"].get_int64(),
            repost_json["owner_id"].get_int64(),
            repost_json["text"].get_c_str().take_value());

        if (repost_json["attachments"].is_array() && repost_json["attachments"].get_array().size() > 0) {
            repost->construct_attachments(event::get_attachments(repost_json["attachments"].get_array()));
        }

        return repost;
    } else {
        throw exception::access_error(-1 ,"Attempting accessing empty repost");
    }
}

std::ostream& operator<<(std::ostream& ostream, const vk::event::wall_post_new& event)
{
    ostream << "wall_post_new:" << std::endl;

    ostream << std::setw(30)
            << "id: " << event.id() << std::endl;
    ostream << std::setw(30)
            << "from_id: " << event.from_id() << std::endl;
    ostream << std::setw(30)
            << "owner_id: " << event.owner_id() << std::endl;
    ostream << std::setw(30)
            << "created_by: " << event.created_by() << std::endl;
    ostream << std::setw(30)
            << "text: " << event.text() << std::endl;
    ostream << std::setw(30)
            << "can_edit? " << std::boolalpha << event.can_edit() << std::endl;
    ostream << std::setw(30)
            << "can_delete? " << std::boolalpha << event.can_delete() << std::endl;
    ostream << std::setw(30)
            << "marked_as_ads? " << std::boolalpha << event.marked_as_ads() << std::endl;

    auto append_attachments = [&ostream](const auto& attachments) {
        for (auto& attachment : attachments) {
            ostream << std::setw(40) << "attachment: ";
            ostream << attachment->value();
            ostream << std::endl;
        }
    };

    if (event.has_attachments()) {
        append_attachments(event.attachments());
    }

    if (event.has_repost()) {
        ostream << "repost:" << std::endl;
        ostream << std::setw(30)
                << "from_id: " << event.repost()->from_id() << std::endl;
        ostream << std::setw(30)
                << "id: " << event.repost()->id() << std::endl;
        ostream << std::setw(30)
                << "owner_id: " << event.repost()->owner_id() << std::endl;
        ostream << std::setw(30)
                << "text: " << event.repost()->text() << std::endl;

        if (!event.repost()->attachments().empty()) {
            append_attachments(event.repost()->attachments());
        }
    }

    return ostream;
}
