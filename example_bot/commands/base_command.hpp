#pragma once

#include <string>

#include "vkapi/include/events/common_event.hpp"

class base_command
{
public:
  virtual void execute(const vk::event::message_new& event) const = 0;
  virtual ~base_command() = default;
};
