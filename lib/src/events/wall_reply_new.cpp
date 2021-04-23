#include "events/wall_reply_new.hpp"

#include "exception/error_processor.hpp"
#include "simdjson.h"

vk::event::wall_reply_new::wall_reply_new(simdjson::dom::object&& event)
  : _event_json(std::make_shared<simdjson::dom::object>(std::move(event)))
  , _attachment_handler()
{
    if (get_event()["attachments"].is_array() && get_event()["attachments"].get_array().size() > 0)
    {
        _has_attachments = true;
    }
}

std::int64_t vk::event::wall_reply_new::id() const noexcept
{
    return get_event()["id"].get_int64();
}

std::int64_t vk::event::wall_reply_new::from_id() const noexcept
{
    return get_event()["from_id"].get_int64();
}

std::int64_t vk::event::wall_reply_new::post_id() const noexcept
{
    return get_event()["post_id"].get_int64();
}

std::int64_t vk::event::wall_reply_new::owner_id() const noexcept
{
    return get_event()["owner_id"].get_int64();
}

std::string vk::event::wall_reply_new::text() const noexcept
{
    return get_event()["text"].get_c_str().take_value();
}

bool vk::event::wall_reply_new::has_attachments() const noexcept
{
    return _has_attachments;
}

vk::attachment::attachments_t vk::event::wall_reply_new::attachments() const
{
    if (_has_attachments)
    {
        return _attachment_handler.try_get(get_event()["attachments"].get_array());
    }
    else
    {
        // Exception thrown there, hence final return will never executed.
        processing::log_and_throw<exception::access_error>("wall_reply_new", "Attempting accessing empty attachment list");
    }
    return {};
}

std::ostream& operator<<(std::ostream& ostream, const vk::event::wall_reply_new& reply)
{
    ostream << "wall_reply_new:" << std::endl;
    ostream << "  "
            << "id:               " << reply.id() << std::endl;
    ostream << "  "
            << "from_id:          " << reply.from_id() << std::endl;
    ostream << "  "
            << "post_id:          " << reply.post_id() << std::endl;
    ostream << "  "
            << "owner_id:         " << reply.owner_id() << std::endl;
    ostream << "  "
            << "text:             " << reply.text() << std::endl;
    ostream << "  "
            << "has_attachments?  " << reply.has_attachments() << std::endl;
    if (reply.has_attachments())
    {
        for (auto& attachment : reply.attachments())
        {
            ostream << "    "
                    << "attachment:       ";
            ostream << attachment->value();
            ostream << std::endl;
        }
    }
    return ostream;
}
