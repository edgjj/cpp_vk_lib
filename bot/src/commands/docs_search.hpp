#ifndef BOT_CONCRETE_COMMAND_H
#define BOT_CONCRETE_COMMAND_H

#include "../commands/base.hpp"
#include "../utils/string_utils.hpp"
#include "cpp_vk_lib/config/loader.hpp"
#include "cpp_vk_lib/events/message_new.hpp"
#include "cpp_vk_lib/methods/docs.hpp"
#include "cpp_vk_lib/methods/messages.hpp"
#include "cpp_vk_lib/oauth/client.hpp"

#include <iostream>


namespace bot {
namespace command {
/*!
 * @brief By design, you have choice:
 *
 *  - load your token from config.json;
 *  - get your token in runtime using OAuth client;
 *
 *  Here is an example that demonstrates how to use OAuth.
 */
class docs_search final : public base
{
public:
    explicit docs_search()
      : m_oauth_client(vk::config::username(), vk::config::password(), vk::oauth::target_client::windows)
      , m_messages(vk::method::messages::disable_mentions)
      , m_docs(m_oauth_client.token())
    {}
    
    void execute(const vk::event::message_new& event) const override
    {
        m_messages.send(event.peer_id(), "Docs: ", {m_docs.search(string_util::cut_first(event.text()), 50)});
    }

private:
    vk::oauth::client m_oauth_client;
    vk::method::messages m_messages;
    vk::method::docs m_docs;
};

}// namespace command
}// namespace bot


#endif// BOT_CONCRETE_COMMAND_H
