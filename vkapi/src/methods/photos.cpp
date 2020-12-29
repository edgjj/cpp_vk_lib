#include <simdjson.h>

#include "vkapi/include/lib/network.hpp"
#include "vkapi/include/methods/photos.hpp"

vk::attachment::attachment_list vk::photos::search(std::string_view query, long count)
{
  return common_search("photos.search", query, count);
}

std::string vk::photos::get_messages_upload_server(long peer_id)
{
  return network->request(append_url("photos.getMessagesUploadServer"), {
    {"access_token",  access_token  },
    {"v",             api_v         },
    {"peer_id",       std::to_string(peer_id)}
  });
}

std::string vk::photos::get_chat_upload_server(long chat_id)
{
  return network->request(append_url("photos.getChatUploadServer"), {
    {"access_token",  access_token  },
    {"v",             api_v         },
    {"crop_x",        "512"         },
    {"crop_y",        "512"         },
    {"chat_id",       std::to_string(chat_id)}
  });
}

std::shared_ptr<vk::attachment::photo_attachment> vk::photos::save_messages_photo(std::string_view file, std::string_view raw_server)
{
  std::string upload_url = static_cast<std::string>(parser->parse(raw_server)["response"]["upload_url"]);

  std::string raw_upload_response = network->upload("file1", file, upload_url);

  simdjson::dom::object upload_response = parser->parse(raw_upload_response);

  if (static_cast<std::string_view>(upload_response["photo"]) == "") return {};

  std::string raw_vk_response =
  network->request(append_url("photos.saveMessagesPhoto"), {
    { "photo",         static_cast<std::string>(upload_response["photo"])},
    { "hash",          static_cast<std::string>(upload_response["hash"])},
    { "server",        std::to_string(static_cast<long>(upload_response["server"]))},
    { "access_token",  access_token },
    { "v",             api_v        }
  });

  simdjson::dom::object uploaded_attachment = parser->parse(raw_vk_response)["response"].at(0);

  long owner_id = static_cast<long>(uploaded_attachment["id"]);
  long id       = static_cast<long>(uploaded_attachment["owner_id"]);

  return std::make_shared<vk::attachment::photo_attachment>(id, owner_id);
}
