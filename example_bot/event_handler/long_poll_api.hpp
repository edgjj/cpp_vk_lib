#pragma once

#include "vkapi/include/events/common_event.hpp"
#include "vkapi/include/api/long_poll_api.hpp"

#include "message_event_handler.hpp"

class long_poll_handler
{
public:
  void loop()
  {
    _lp_data = _lp_api.get_server();

    while(true)
    {
      for (const vk::event::common& event : _lp_api.listen(_lp_data))
      {
        if (event.type() == "message_new") _message_handler.process(event.get_message_event());

        _lp_data.ts = event.ts();
      }
    }
  }

private:
  vk::long_poll_api _lp_api;
  vk::long_poll_data _lp_data;

  message_event_handler _message_handler;
};
