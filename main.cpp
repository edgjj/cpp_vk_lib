#include <iostream>

#include "vkapi/include/methods/messages.hpp"
#include "vkapi/include/methods/audio.hpp"
#include "vkapi/include/methods/docs.hpp"
#include "vkapi/include/methods/photos.hpp"
#include "vkapi/include/methods/video.hpp"
#include "vkapi/include/api/long_poll_api.hpp"


void photo_upload(vk::photos& photos, vk::messages& messages)
{
  std::string raw_json = photos.get_messages_upload_server(2000000008);
  std::shared_ptr<vk::attachment::photo_attachment> attachment = photos.save_messages_photo("/home/machen/cat.jpg", raw_json);
  messages.send(2000000008, "at", { attachment });
}


void docs_upload(vk::docs& docs)
{
  std::string raw_json = docs.get_upload_server(192764727);
  std::shared_ptr<vk::attachment::document_attachment> attachment = docs.save("/home/machen/cat.jpg", raw_json);
}


void upload_audio_to_user_playlist(vk::audio& audio)
{
  std::string raw_json = audio.get_upload_server();
  audio.save("`Maxwell", "`Balla balla", "/home/machen/balla.mp3", raw_json);
}


void chat_photo_upload(vk::photos& photos, vk::messages& messages)
{
  std::string raw_json = photos.get_chat_upload_server(8);
  messages.set_chat_photo("/home/machen/PICS/govnokod.jpg", raw_json);
}


void test_uploader()
{
  vk::photos photos;
  vk::docs docs;
  vk::audio audio;
  vk::messages messages;

  photo_upload(photos, messages);
//  docs_upload(docs);
  upload_audio_to_user_playlist(audio);
  chat_photo_upload(photos, messages);
}


void search_attachments(const vk::update::message_new& update, vk::messages& messages)
{
  vk::docs docs;
  vk::attachment::attachment_list list = docs.search(update.text(), 10);

  if (list.empty()) { messages.send(update.peer_id(), "no documents found"); return; }

  std::string urls;
  for (auto&& it : list)
  {
    auto doc = vk::attachment::document_cast(it);
    urls += "url: " + doc->raw_url() + '\n';
  }
  messages.send(update.peer_id(), urls, list);
}


void get_user_attachments(const vk::update::message_new& update, vk::messages& messages)
{
  vk::attachment::attachment_list list = update.attachments();

  messages.send(update.peer_id(), "attachments count: " + std::to_string(list.size()), list);
}


void check_reply_message(const vk::update::message_new& update, vk::messages& messages)
{
  (update.has_reply())
  ? messages.send(update.peer_id(), update.reply().text())
  : messages.send(update.peer_id(), "no reply detected");
}


void process_messages(const vk::update::message_new& update, vk::messages& messages)
{
  search_attachments(update, messages);
}


void process_updates(vk::long_poll_data& data, vk::long_poll_api& lp_api, vk::messages& messages)
{
  for (const vk::update::common& common : lp_api.listen(data))
  {
    if (common.type() == "message_new")
    {
      process_messages(common.get_message_update(), messages);
      data.ts = common.ts();
    }
  }
}


int main(void)
{
  test_uploader();
}

//int main(void)
//{
//  vk::long_poll_api lp_api;
//  vk::long_poll_data lp_data;
//  vk::messages messages;

//  lp_data = lp_api.get_server();

//  while (true)
//  {
//    process_updates(lp_data, lp_api, messages);
//  }
//}

