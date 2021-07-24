#ifndef BOT_LONG_POLLER_HPP
#define BOT_LONG_POLLER_HPP

#include "../handlers/message_handler.hpp"

#include "cpp_vk_lib/long_poll/api.hpp"

namespace bot {

class long_poller
{
public:
    explicit long_poller()
      : m_data(m_api.server()) {}

    message_handler& get_message_handler() noexcept
    {
        return m_message_handler;
    }

    int run()
    {
        while (true) {
            auto events = m_api.listen(m_data);

            for (auto& event : events) {
                m_api.on_event("message_new", *event, [this, &event] {
                    std::cout << event->get_message_event() << std::endl;
                    m_message_handler.process(event->get_message_event());
                });
            }
            m_api.run();
        }
        return EXIT_SUCCESS;
    }

private:
    vk::long_poll::api m_api{};
    vk::long_poll::data m_data;
    message_handler m_message_handler{};
};

}// namespace bot

#endif// BOT_LONG_POLLER_HPP
