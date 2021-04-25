#include "events/wall_post_new.hpp"

#include "exception/error_processor.hpp"
#include "misc/cppdefs.hpp"
#include "simdjson.h"

vk::event::wall_post_new::wall_post_new(simdjson::dom::object&& event)
  : m_event_json(std::make_shared<simdjson::dom::object>(std::move(event)))
  , m_attachment_handler()
{
    if (get_event()["attachments"].is_array())
    {
        m_has_attachments = true;
    }

    if (get_event()["copy_history"].is_array())
    {
        m_has_repost = true;
    }
}

std::int64_t vk::event::wall_post_new::id() const noexcept
{
    return get_event()["id"].get_int64();
}

std::int64_t vk::event::wall_post_new::from_id() const noexcept
{
    return get_event()["from_id"].get_int64();
}

std::int64_t vk::event::wall_post_new::owner_id() const noexcept
{
    return get_event()["owner_id"].get_int64();
}

std::int64_t vk::event::wall_post_new::created_by() const noexcept
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

vk::attachment::attachments_t vk::event::wall_post_new::attachments() const noexcept
{
    if (vk_likely(m_has_attachments))
    {
        return m_attachment_handler.try_get(get_event()["attachments"].get_array());
    }
    else
    {
        // Exception thrown there, hence final return will never executed.
        processing::log_and_throw<exception::access_error>("wall_post_new", "Attempting accessing empty attachment list.");
    }
    return {};
}

std::shared_ptr<vk::event::wall_repost> vk::event::wall_post_new::repost() const
{
    simdjson::dom::object repost_json = get_event()["copy_history"].get_array().at(0).get_object();

    if (vk_likely(m_has_repost))
    {
        std::shared_ptr<wall_repost> repost = std::make_shared<wall_repost>(
            repost_json["id"].get_int64(),
            repost_json["from_id"].get_int64(),
            repost_json["owner_id"].get_int64(),
            repost_json["text"].get_c_str().take_value());
        if (repost_json["attachments"].is_array() && repost_json["attachments"].get_array().size() > 0)
        {
            repost->construct_attachments(m_attachment_handler.try_get(repost_json["attachments"].get_array()));
        }
        return repost;
    }
    else
    {
        // Exception thrown there, hence final return will never executed.
        processing::log_and_throw<exception::access_error>("wall_post_new", "Attempting accessing empty repost.");
    }
    return {};
}

std::ostream& operator<<(std::ostream& ostream, const vk::event::wall_post_new& event)
{
    ostream << "wall_post_new:" << std::endl;
    ostream << "  "
            << "id:             " << event.id() << std::endl;
    ostream << "  "
            << "from_id:        " << event.from_id() << std::endl;
    ostream << "  "
            << "owner_id:       " << event.owner_id() << std::endl;
    ostream << "  "
            << "created_by:     " << event.created_by() << std::endl;
    ostream << "  "
            << "text:           " << event.text() << std::endl;
    ostream << "  "
            << "can_edit?       " << std::boolalpha << event.can_edit() << std::endl;
    ostream << "  "
            << "can_delete?     " << std::boolalpha << event.can_delete() << std::endl;
    ostream << "  "
            << "marked_as_ads?  " << std::boolalpha << event.marked_as_ads() << std::endl;

    auto append_attachments = [&ostream](const auto& attachments) {
        for (auto& attachment : attachments)
        {
            ostream << '\t' << "attachment:                ";
            ostream << attachment->value();
            ostream << std::endl;
        }
    };

    if (event.has_attachments())
    {
        append_attachments(event.attachments());
    }

    if (event.has_repost())
    {
        ostream << "  "
                << "repost:" << std::endl;
        ostream << "  "
                << "  "
                << "from_id:    " << event.repost()->from_id() << std::endl;
        ostream << "  "
                << "  "
                << "id:         " << event.repost()->id() << std::endl;
        ostream << "  "
                << "  "
                << "owner_id:   " << event.repost()->owner_id() << std::endl;
        ostream << "  "
                << "  "
                << "text:       " << event.repost()->text() << std::endl;

        if (!event.repost()->attachments().empty())
        {
            append_attachments(event.repost()->attachments());
        }
    }
    return ostream;
}
