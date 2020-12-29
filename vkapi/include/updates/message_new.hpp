#pragma once

#include <list>

#include "vkapi/include/attachment/attachment.hpp"

namespace simdjson::dom
{
class object;
class array;
}

namespace vk::update
{
class message_new
{
public:
  message_new(std::string_view raw_json);

  message_new reply() const;
  std::string text()  const noexcept;
  long from_id()      const noexcept;
  long peer_id()      const noexcept;
  bool has_reply()    const noexcept;
  attachment::attachment_list attachments() const noexcept;

private:
  message_new(long peer_id, long from_id, std::string_view text);
  void get_reply(const simdjson::dom::object& object);
  void get_attachments(const simdjson::dom::array& attachments);

  long _peer_id;
  long _from_id;
  std::string _text;
  message_new* _reply;
  attachment::attachment_list _attachments;
  bool _is_reply = false;
};
}
