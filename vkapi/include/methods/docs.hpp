#pragma once

#include "vkapi/include/document/common_document.hpp"

namespace vk
{
class docs : private document::common
{
public:
  vk::attachment::attachment_list search(std::string_view query, long count) const;
  std::string get_upload_server(long group_id) const;
  std::shared_ptr<vk::attachment::document_attachment> save(std::string_view file, std::string_view raw_server);
};
}
