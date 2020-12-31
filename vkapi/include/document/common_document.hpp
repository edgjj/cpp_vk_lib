#pragma once

#include "vkapi/include/attachment/attachment.hpp"
#include "vkapi/include/api/base_object.hpp"

namespace vk::document
{
class common : public base_object
{
public:
  vk::attachment::attachment_list common_search(std::string_view type, std::string_view query, std::int64_t count) const;
  virtual ~common() = default;
};
}
