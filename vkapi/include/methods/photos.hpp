#pragma once

#include "vkapi/include/document/common_document.hpp"

namespace vk
{
class photos : private document::common
{
public:
  vk::attachment::attachment_list search(std::string_view query, long count);
  std::string get_messages_upload_server(long peer_id);
  std::string get_chat_upload_server(long chat_id);
  std::shared_ptr<vk::attachment::photo_attachment> save_messages_photo(std::string_view file, std::string_view raw_server);
};
}
