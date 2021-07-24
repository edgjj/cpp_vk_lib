#ifndef BOT_COMMANDS_KEYBOARD_HPP
#define BOT_COMMANDS_KEYBOARD_HPP

#include "../commands/base.hpp"

#include "cpp_vk_lib/events/message_new.hpp"
#include "cpp_vk_lib/keyboard/layout.hpp"
#include "cpp_vk_lib/methods/messages.hpp"

namespace bot {
namespace command {

class keyboard final : public base
{
public:
    /// @note vk::keyboard::layout has `none` flag by default, which corresponds to white color.
    explicit keyboard()
        : m_layout(std::make_unique<vk::keyboard::layout>(vk::keyboard::flag::in_line))
        , m_messages(vk::method::messages::disable_mentions)
    {
        setup_keyboard();
    }

    void execute(const vk::event::message_new& event) const override
    {
        m_messages.send(event.peer_id(), "Here is keyboard:", m_layout->get());
    }

private:
    void setup_keyboard()
    {
        m_layout->add_row(
            {vk::keyboard::button::text(vk::keyboard::color::blue, "Text 1"),
             vk::keyboard::button::text(vk::keyboard::color::blue, "Text 2")});
        m_layout->add_row({vk::keyboard::button::location()});
        m_layout->add_row({vk::keyboard::button::vk_pay("action=transfer-to-group&group_id=181108510&aid=10")});
        m_layout->serialize();
    }

    std::unique_ptr<vk::keyboard::layout> m_layout;
    vk::method::messages m_messages;
};

}// namespace command
}// namespace bot

#endif// BOT_COMMANDS_KEYBOARD_HPP
