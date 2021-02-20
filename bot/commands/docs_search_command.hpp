#ifndef BOT_CONCRETE_COMMAND_H
#define BOT_CONCRETE_COMMAND_H

#include <iostream>

#include "events/message_new.hpp"
#include "methods/messages.hpp"
#include "methods/docs.hpp"

#include "../commands/base_command.hpp"
#include "../utils/string_utils.hpp"


class docs_search_command final : public base_command {
public:
  void execute(vk::event::message_new& event) override {
    messages.send(event.peer_id(), "Docs: ", { docs.search(string_util::cut_first(event.text()), 50) });
  }
private:
  vk::method::messages messages;
  vk::method::docs docs;
};

#endif // BOT_CONCRETE_COMMAND_H
