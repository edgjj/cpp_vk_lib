#ifndef BOT_SET_CHAT_PHOTO_COMMAND_H
#define BOT_SET_CHAT_PHOTO_COMMAND_H

#include "../commands/base.hpp"
#include "cpp_vk_lib/events/message_new.hpp"
#include "cpp_vk_lib/methods/messages.hpp"
#include "cpp_vk_lib/methods/photos.hpp"
#include "cpp_vk_lib/net/request_manager.hpp"


namespace bot {
namespace command {

class set_chat_photo final : public base
{
public:
    explicit set_chat_photo()
      : m_photos()
      , m_messages(vk::method::messages::disable_mentions)
    {}
    void execute(const vk::event::message_new& event) const override
    {
        std::string raw_upload_json = m_photos.get_chat_upload_server(event.peer_id());
        m_messages.set_chat_photo("/path/to/photo.png", raw_upload_json);
    }

private:
    vk::method::photos m_photos;
    vk::method::messages m_messages;
};
}// namespace command
}// namespace bot

#endif// BOT_SET_CHAT_PHOTO_COMMAND_H
