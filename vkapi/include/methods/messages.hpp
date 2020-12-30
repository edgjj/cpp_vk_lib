#pragma once

#include <map>
#include "vkapi/include/api/base_object.hpp"
#include "vkapi/include/attachment/attachment.hpp"

namespace vk
{
class messages : private base_object
{
public:
  void send(long peer_id, std::string_view text) const;
  void send(long peer_id, std::string_view text, const attachment::attachment_list& list) const;
  void remove_chat_user(long chat_id, long user_id) const;
  void edit_chat(long chat_id, std::string_view new_title) const;
  void set_chat_photo(std::string_view filename, std::string_view raw_server) const;
};
}
