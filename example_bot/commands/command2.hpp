#pragma once

#include <string>

#include "commands/base_command.hpp"

class second_command : public base_command
{
public:
  std::string execute(std::string_view text) const override
  {
    return std::string { "Second command returned: " } + text.data();
  }
};
