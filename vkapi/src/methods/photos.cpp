#include <simdjson.h>

#include "vkapi/include/lib/network.hpp"
#include "vkapi/include/methods/photos.hpp"

vk::attachment::attachment_list vk::photos::search(std::string_view query, std::int64_t count) const
{
  return common_search("photos.search", query, count);
}

std::string vk::photos::get_messages_upload_server(std::int64_t peer_id) const
{
  return network->request(append_url("photos.getMessagesUploadServer"), {
    {"access_token",  access_token  },
    {"v",             api_v         },
    {"peer_id",       std::to_string(peer_id)}
  });
}

std::string vk::photos::get_chat_upload_server(std::int64_t chat_id) const
{
  return network->request(append_url("photos.getChatUploadServer"), {
    {"access_token",  access_token  },
    {"v",             api_v         },
    {"crop_x",        "512"         },
    {"crop_y",        "512"         },
    {"chat_id",       std::to_string(chat_id - 2000000000)}
  });
}

std::shared_ptr<vk::attachment::photo_attachment> vk::photos::save_messages_photo(std::string_view filename, std::string_view raw_server) const
{
  std::string upload_url = static_cast<std::string>(parser->parse(raw_server)["response"]["upload_url"]);

  std::string raw_upload_response = network->upload("file1", filename, upload_url);

  simdjson::dom::object upload_response = parser->parse(raw_upload_response);

  if (static_cast<std::string_view>(upload_response["photo"]) == "") return {};

  std::string raw_vk_response =
  network->request(append_url("photos.saveMessagesPhoto"), {
    { "photo",         static_cast<std::string>(upload_response["photo"])},
    { "hash",          static_cast<std::string>(upload_response["hash"])},
    { "server",        std::to_string(static_cast<std::int64_t>(upload_response["server"]))},
    { "access_token",  access_token },
    { "v",             api_v        }
  });

  simdjson::dom::object uploaded_attachment = parser->parse(raw_vk_response)["response"].at(0);

  std::int64_t owner_id = static_cast<std::int64_t>(uploaded_attachment["id"]);
  std::int64_t id       = static_cast<std::int64_t>(uploaded_attachment["owner_id"]);

  return std::make_shared<vk::attachment::photo_attachment>(id, owner_id);
}
