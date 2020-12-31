#pragma once

#include "vkapi/include/document/common_document.hpp"

namespace vk
{
class video : private document::common
{
public:
  vk::attachment::attachment_list search(std::string_view query, std::int64_t count) const;
};
}
