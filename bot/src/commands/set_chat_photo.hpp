#ifndef BOT_SET_CHAT_PHOTO_COMMAND_H
#define BOT_SET_CHAT_PHOTO_COMMAND_H

#include "cpp_vk_lib/events/message_new.hpp"
#include "cpp_vk_lib/methods/messages.hpp"
#include "cpp_vk_lib/methods/photos.hpp"
#include "cpp_vk_lib/net/client.hpp"

#include "../commands/base.hpp"


namespace bot {
namespace command {

class set_chat_photo_command final : public base_command {
public:
  explicit set_chat_photo_command()
    : photos()
    , messages(vk::method::messages::disable_mentions) {}
  void execute (const vk::event::message_new& event) const override {
    std::string raw_upload_json =
      photos.get_chat_upload_server(event.peer_id());
    messages.set_chat_photo("/path/to/image.{png|jpg}", raw_upload_json);
  }
private:
  vk::method::photos photos;
  vk::method::messages messages;
};
} // namespace command
} // namespace bot

#endif // BOT_SET_CHAT_PHOTO_COMMAND_H
