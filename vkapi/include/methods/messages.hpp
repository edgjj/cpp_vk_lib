#pragma once

#include <map>
#include "vkapi/include/api/base_object.hpp"
#include "vkapi/include/attachment/attachment.hpp"

namespace vk
{
class messages : private base_object
{
public:
  void send(std::int64_t peer_id, std::string_view text) const;
  void send(std::int64_t peer_id, std::string_view text, const attachment::attachment_list& list) const;
  void remove_chat_user(std::int64_t chat_id, std::int64_t user_id) const;
  void edit_chat(std::int64_t chat_id, std::string_view new_title) const;
  void set_chat_photo(std::string_view filename, std::string_view raw_server) const;
};
}
