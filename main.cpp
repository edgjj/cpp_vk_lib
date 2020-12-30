#include <iostream>

#include "vkapi/include/lib/network.hpp"

#include "vkapi/include/methods/audio.hpp"
#include "vkapi/include/methods/docs.hpp"
#include "vkapi/include/methods/messages.hpp"
#include "vkapi/include/methods/photos.hpp"
#include "vkapi/include/methods/video.hpp"
#include "vkapi/include/api/long_poll_api.hpp"


void download_voice_message(const vk::event::message_new& message_event, vk::messages& messages)
{
  vk::lib::network network;
  for (auto&& attachment : message_event.attachments())
  {
    if (attachment->type() == "audio_message")
    {
      auto audio_message = vk::attachment::audio_message_cast(attachment);

      messages.send(message_event.peer_id(), "downloading...");
      (network.download("/home/machen/voice.mp3", audio_message->raw_mp3()) == 0)
        ? messages.send(message_event.peer_id(), "downloaded")
        : messages.send(message_event.peer_id(), "error");
    }
  }
}

void photo_upload(vk::photos& photos, vk::messages& messages)
{
  std::string raw_json = photos.get_messages_upload_server(2000000008);
  std::shared_ptr<vk::attachment::photo_attachment> attachment = photos.save_messages_photo("/home/machen/cat.jpg", raw_json);
  messages.send(2000000008, "attachment: ", { attachment });
}


void docs_upload(vk::docs& docs)
{
  std::string raw_json = docs.get_upload_server(192764727);
  std::shared_ptr<vk::attachment::document_attachment> attachment = docs.save("/home/machen/cat.jpg", raw_json);
}


void upload_audio_to_user_playlist(vk::audio& audio)
{
  std::string raw_json = audio.get_upload_server();
  audio.save("`LX & `Maxwell", "`Diese `Beiden", "/home/machen/Diese Beiden.mp3", raw_json);
}


void chat_photo_upload(vk::photos& photos, vk::messages& messages)
{
  std::string raw_json = photos.get_chat_upload_server(2000000008);
  messages.set_chat_photo("/home/machen/PICS/govnokod.jpg", raw_json);
}


void search_docs(const vk::event::message_new& update, vk::messages& messages)
{
  vk::docs docs;
  vk::attachment::attachment_list media = docs.search(update.text(), 10);

  (media.empty())
    ? messages.send(update.peer_id(), "no docs")
    : messages.send(update.peer_id(), "docs: ", media);
}


void search_videos(const vk::event::message_new& update, vk::messages& messages)
{
  vk::video video;
  vk::attachment::attachment_list media = video.search(update.text(), 10);

  (media.empty())
    ? messages.send(update.peer_id(), "no videos")
    : messages.send(update.peer_id(), "videos: ", media);
}


void search_photos(const vk::event::message_new& update, vk::messages& messages)
{
  vk::photos photos;
  vk::attachment::attachment_list media = photos.search(update.text(), 10);

  (media.empty())
    ? messages.send(update.peer_id(), "no photos")
    : messages.send(update.peer_id(), "photos: ", media);
}


void search_attachments(const vk::event::message_new& update, vk::messages& messages)
{
  search_docs(update, messages);
  search_photos(update, messages);
  search_videos(update, messages);
}


void send_wall_post(const vk::event::common& update, vk::messages& messages)
{
  vk::event::wall_post_new wall_post = update.get_wall_post_event();

  auto attachment =
  std::make_shared<vk::attachment::wall_attachment>(
    wall_post.from_id(),
    wall_post.id()
  );

  messages.send(2000000008, "post: ", { attachment });
}


void get_user_attachments(const vk::event::message_new& update, vk::messages& messages)
{
  vk::attachment::attachment_list list = update.attachments();

  for (const std::shared_ptr<vk::attachment::base_attachment>& attachment : list)
  {
    if (attachment->type() == "photo")
    {
      std::shared_ptr<vk::attachment::photo_attachment> photo = vk::attachment::photo_cast(attachment);

      messages.send(update.peer_id(), "photo: ", { photo });
    }
  }

  messages.send(update.peer_id(), "attachments count: " + std::to_string(list.size()), list);
}


void check_reply_message(const vk::event::message_new& update, vk::messages& messages)
{
  (update.has_reply())
  ? messages.send(update.peer_id(), update.reply().text())
  : messages.send(update.peer_id(), "no reply detected");
}


void process_messages(const vk::event::message_new& update, vk::messages& messages)
{
  search_attachments(update, messages);
}


void process_updates(vk::long_poll_data& data, vk::long_poll_api& lp_api, vk::messages& messages)
{
  for (const vk::event::common& common_update : lp_api.listen(data))
  {
    if (common_update.type() == "message_new")
    {
//      get_user_attachments(common_update.get_message_event(), messages);
//      search_attachments(common_update.get_message_event(), messages);
//      process_messages(common_update.get_message_event(), messages);
//      check_reply_message(common_update.get_message_event(), messages);
      download_voice_message(common_update.get_message_event(), messages);
    }
    if (common_update.type() == "wall_post_new")
    {
//      send_wall_post(common_update, messages);
    }
    data.ts = common_update.ts();
  }
}

int main(void)
{
  vk::long_poll_api lp_api;
  vk::long_poll_data lp_data;
  vk::messages messages;

  lp_data = lp_api.get_server();

  while (true)
  {
    process_updates(lp_data, lp_api, messages);
  }
}

