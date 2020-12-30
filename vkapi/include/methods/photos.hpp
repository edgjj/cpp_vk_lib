#pragma once

#include "vkapi/include/document/common_document.hpp"

namespace vk
{
class photos : private document::common
{
public:
  vk::attachment::attachment_list search(std::string_view query, long count) const;
  std::string get_messages_upload_server(long peer_id) const;
  std::string get_chat_upload_server(long chat_id) const;
  std::shared_ptr<vk::attachment::photo_attachment> save_messages_photo(std::string_view filename, std::string_view raw_server) const;
};
}
