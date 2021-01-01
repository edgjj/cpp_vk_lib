#include <simdjson.h>

#include "vkapi/include/lib/network.hpp"
#include "vkapi/include/methods/docs.hpp"

vk::attachment::attachment_list vk::docs::search(std::string_view query, std::int64_t count) const
{
  return common_search("docs.search", query, count);
}

std::string vk::docs::get_upload_server(std::int64_t group_id) const
{
  return network->request(append_url("docs.getUploadServer"), {
    { "access_token",  access_token  },
    { "v",             api_v         },
    { "group_id",      std::to_string(group_id)}
  });
}

std::string vk::docs::get_messages_upload_server(std::string_view type, int64_t peer_id) const
{
  return network->request(append_url("docs.getMessagesUploadServer"), {
    { "access_token",  access_token   },
    { "peer_id",       std::to_string(peer_id)},
    { "type",          type.data()    },
    { "v",             api_v          },
  });
}

std::shared_ptr<vk::attachment::audio_message_attachment> vk::docs::save_audio_message(std::string_view filename, std::string_view raw_server)
{
  std::string upload_url = static_cast<std::string>(parser->parse(raw_server)["response"]["upload_url"]);

  std::string raw_upload_response = network->upload("file", filename, upload_url);

  std::string upload_response = static_cast<std::string_view>(parser->parse(raw_upload_response)["file"]).data();

  if (upload_response == "") return {};

  std::string raw_save_response =
  network->request(append_url("docs.save"), {
    { "file",          upload_response  },
    { "title",         "voice"          },
    { "access_token",  access_token     },
    { "v",             api_v            }
  });

  simdjson::dom::object uploaded_doc = parser->parse(raw_save_response)["response"]["audio_message"];

  return
  std::make_shared<vk::attachment::audio_message_attachment>(
    static_cast<std::int64_t>(uploaded_doc["owner_id"]),
    static_cast<std::int64_t>(uploaded_doc["id"]),
    static_cast<std::string_view>(uploaded_doc["link_ogg"]),
    static_cast<std::string_view>(uploaded_doc["link_mp3"])
  );
}
