#pragma once

#include <map>
#include "vkapi/include/api/base_object.hpp"

namespace vk
{
class messages : private base_object
{
public:
  void send(long peer_id, std::string_view text);
  void send(long peer_id, std::string_view text, const attachment::attachment_list& list);
  void remove_chat_user(long chat_id, long user_id);
  void edit_chat(long chat_id, std::string_view new_title);
  void set_chat_photo(std::string_view filename, std::string_view raw_server);
};
}
