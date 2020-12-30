#pragma once

#include "commands/base_command.hpp"

class first_command : public base_command
{
public:
  std::string execute(std::string_view text) const override
  {
    return std::string { "First command returned: " } + text.data();
  }
};
