#pragma once

#include <string>

class base_command
{
public:
  virtual std::string execute(std::string_view) const = 0;
};
