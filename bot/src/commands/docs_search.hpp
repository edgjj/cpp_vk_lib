#ifndef BOT_CONCRETE_COMMAND_H
#define BOT_CONCRETE_COMMAND_H

#include "events/message_new.hpp"
#include "methods/messages.hpp"
#include "methods/docs.hpp"

#include "../commands/base.hpp"
#include "../utils/string_utils.hpp"


namespace bot {
namespace command {

class docs_search_command final : public base_command {
public:
  void execute(const vk::event::message_new& event) const override {
    messages.send(event.peer_id(), "Docs: ", { docs.search(string_util::cut_first(event.text()), 50) });
  }
private:
  vk::method::messages messages{vk::method::messages::disable_mentions};
  vk::method::docs docs;
};

} // namespace command
} // namespace bot


#endif // BOT_CONCRETE_COMMAND_H
