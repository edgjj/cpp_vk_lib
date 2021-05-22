#include "events/message_new.hpp"

#include "exception/error-inl.hpp"
#include "simdjson.h"

vk::event::message_new::~message_new() = default;

vk::event::message_new::message_new(simdjson::dom::object&& event)
  : m_event_json(std::make_shared<simdjson::dom::object>(std::move(event)))
  , m_action()
  , m_attachment_handler()
{
    if (get_event()["reply_message"].is_object())
    {
        m_has_reply = true;
    }

    if (get_event()["attachments"].is_array())
    {
        m_has_attachments = true;
    }

    if (get_event()["fwd_messages"].is_array() && get_event()["fwd_messages"].get_array().size() != 0)
    {
        m_has_attachments = true;
    }

    if (get_event()["action"].is_object())
    {
        m_has_action = true;
        try_get_actions();
    }
}

void vk::event::message_new::try_get_actions()
{
    simdjson::dom::object action = get_event()["action"].get_object();
    std::string action_name = action["type"].get_string().take_value().data();
    if (action_name == "chat_invite_user")
    {
        m_action = action::chat_invite_user{action["member_id"].get_int64()};
    }
    if (action_name == "chat_kick_user")
    {
        m_action = action::chat_kick_user{action["member_id"].get_int64()};
    }
    if (action_name == "chat_pin_message")
    {
        m_action = action::chat_pin_message{
            action["member_id"].get_int64(),
            action["conversation_message_id"].get_int64(),
            action["message"].get_c_str().take_value()};
    }
    if (action_name == "chat_unpin_message")
    {
        m_action = action::chat_unpin_message{action["member_id"].get_int64(), action["conversation_message_id"].get_int64()};
    }
    if (action_name == "chat_photo_update")
    {
        m_action = action::chat_photo_update{
            // empty
        };
    }
    if (action_name == "chat_title_update")
    {
        m_action = action::chat_title_update{action["text"].get_c_str().take_value()};
    }
}

bool vk::event::message_new::on_action(std::string_view action_type) const noexcept
{
    if (action_type == "chat_invite_user")
    {
        return std::holds_alternative<action::chat_invite_user>(m_action);
    }
    if (action_type == "chat_kick_user")
    {
        return std::holds_alternative<action::chat_kick_user>(m_action);
    }
    if (action_type == "chat_pin_message")
    {
        return std::holds_alternative<action::chat_pin_message>(m_action);
    }
    if (action_type == "chat_unpin_message")
    {
        return std::holds_alternative<action::chat_unpin_message>(m_action);
    }
    if (action_type == "chat_photo_update")
    {
        return std::holds_alternative<action::chat_photo_update>(m_action);
    }
    if (action_type == "chat_title_update")
    {
        return std::holds_alternative<action::chat_title_update>(m_action);
    }
    return false;
}

simdjson::dom::object& vk::event::message_new::get_event() const
{
    return *m_event_json;
}

std::int64_t vk::event::message_new::conversation_message_id() const noexcept
{
    return get_event()["conversation_message_id"].get_int64();
}

std::int64_t vk::event::message_new::peer_id() const noexcept
{
    return get_event()["peer_id"].get_int64();
}

std::int64_t vk::event::message_new::from_id() const noexcept
{
    return get_event()["from_id"].get_int64();
}

std::string vk::event::message_new::text() const noexcept
{
    return get_event()["text"].get_c_str().take_value();
}

bool vk::event::message_new::has_action() const noexcept
{
    return m_has_action;
}

bool vk::event::message_new::has_reply() const noexcept
{
    return m_has_reply;
}

bool vk::event::message_new::has_fwd_messages() const noexcept
{
    return m_has_attachments;
}

vk::action::any_action vk::event::message_new::action() const
{
    if (m_has_action)
    {
        return m_action;
    }
    else
    {
        // Exception thrown there, hence final return will never executed.
        throw exception::access_error(-1, "Attempting accessing empty action");
    }
    return {};
}

vk::attachment::attachments_t vk::event::message_new::attachments() const
{
    if (m_has_attachments)
    {
        return m_attachment_handler.try_get(get_event()["attachments"].get_array());
    }
    else
    {
        // Exception thrown there, hence final return will never executed.
        throw exception::access_error (-1, "Attempting accessing empty attachment list");
    }
    return {};
}

std::vector<std::unique_ptr<vk::event::message_new>> vk::event::message_new::fwd_messages() const
{
    if (m_has_attachments)
    {
        std::vector<std::unique_ptr<message_new>> fwd_messages;
        for (const simdjson::dom::element& fwd_message : get_event()["fwd_messages"].get_array())
        {
            fwd_messages.emplace_back(std::make_unique<message_new>(fwd_message));
        }
        return fwd_messages;
    }
    else
    {
        // Exception thrown there, hence final return will never executed.
        throw exception::access_error(-1, "Attempting accessing empty forward messages list");
    }
    return {};
}

std::shared_ptr<vk::event::message_new> vk::event::message_new::reply() const
{
    if (m_has_reply)
    {
        return std::make_unique<message_new>(get_event()["reply_message"].get_object());
    }
    else
    {
        // Exception thrown there, hence final return will never executed.
       throw exception::access_error(-1, "Attempting accessing empty reply");
    }
    return {};
}

std::ostream& operator<<(std::ostream& ostream, const vk::event::message_new& event)
{
    ostream << "message_new:" << std::endl;
    ostream << "  "
            << "conversation_message_id:   " << event.conversation_message_id() << std::endl;
    ostream << "  "
            << "peer_id:                   " << event.peer_id() << std::endl;
    ostream << "  "
            << "from_id:                   " << event.from_id() << std::endl;
    ostream << "  "
            << "text:                      " << event.text() << std::endl;
    ostream << "  "
            << "has_action:                " << event.has_action() << std::endl;
    ostream << "  "
            << "has_reply:                 " << event.has_reply() << std::endl;
    ostream << "  "
            << "has_fwd_messages:          " << event.has_fwd_messages() << std::endl;
    if (event.has_reply())
    {
        ostream << "  "
                << "reply:                     " << event.reply() << std::endl;
    }
    if (event.has_action())
    {
        if (event.on_action("chat_invite_user"))
        {
            ostream << "  "
                    << "chat_invite_user action:   ";
            ostream << std::get<vk::action::chat_invite_user>(event.action()).member_id;
            ostream << std::endl;
        }
        if (event.on_action("chat_kick_user"))
        {
            ostream << "  "
                    << "chat_kick_user action:     ";
            ostream << std::get<vk::action::chat_kick_user>(event.action()).member_id;
            ostream << std::endl;
        }
        if (event.on_action("chat_pin_message"))
        {
            ostream << "  "
                    << "chat_pin_message action:   ";
            ostream << std::get<vk::action::chat_pin_message>(event.action()).member_id;
            ostream << std::endl;
        }
        if (event.on_action("chat_unpin_message"))
        {
            ostream << "  "
                    << "chat_unpin_message action: ";
            ostream << std::get<vk::action::chat_unpin_message>(event.action()).member_id;
            ostream << std::endl;
        }
        if (event.on_action("chat_photo_update"))
        {
            ostream << "  "
                    << "chat_photo_update action:  ";
            ostream << "<empty>";
            ostream << std::endl;
        }
        if (event.on_action("chat_title_update"))
        {
            ostream << "  "
                    << "chat_title_update action:  ";
            ostream << std::get<vk::action::chat_title_update>(event.action()).text;
            ostream << std::endl;
        }
    }
    for (auto& attachment : event.attachments())
    {
        ostream << "  "
                << "attachment:                ";
        ostream << attachment->value();
        ostream << std::endl;
    }
    if (event.has_fwd_messages())
    {
        for (auto& message : event.fwd_messages())
        {
            ostream << "  "
                    << "fwd_message:               ";
            ostream << message.get();
            ostream << std::endl;
        }
    }
    return ostream;
}
