#include <simdjson.h>

#include "vkapi/include/lib/common_error.hpp"
#include "vkapi/include/lib/network.hpp"
#include "vkapi/include/methods/messages.hpp"

void vk::messages::send(long peer_id, std::string_view text)
{
  std::map<std::string, std::string> parameters = {
    { "message",      text.data()  },
    { "peer_id",      std::to_string(peer_id) },
    { "random_id",    "0"          },
    { "access_token", access_token },
    { "v",            api_v        },
    { "disable_mentions", "1"      }
  };
  network->request(append_url("messages.send"), parameters);
}

void vk::messages::send(long peer_id, std::string_view text, const vk::attachment::attachment_list& list)
{
  std::map<std::string, std::string> parameters = {
    { "message",      text.data()  },
    { "peer_id",      std::to_string(peer_id) },
    { "random_id",    "0"          },
    { "access_token", access_token },
    { "v",            api_v        },
    { "disable_mentions", "1"      }
  };
  std::string attachments;
  for (auto&& attachment : list)
  {
    attachments += attachment->value() + ',';
  }
  parameters.insert({{"attachment", attachments}});
  network->request(append_url("messages.send"), parameters);
}

void vk::messages::remove_chat_user(long chat_id, long user_id)
{
  std::string response
  = network->request(append_url("messages.removeChatUser"), {
    { "chat_id",      std::to_string(chat_id) },
    { "user_id",      std::to_string(user_id) },
    { "random_id",    "0"          },
    { "access_token", access_token },
    { "v",            api_v        }
  });

  simdjson::dom::object parsed = parser->parse(response);

  if (not parsed["error"].is_null() && static_cast<long>(parsed["error"]["error_code"]) == 100)
  {
    throw lib::common_error(__FILE__, __LINE__, 100, "Can't kick this user/group.");
  }
  if (not parsed["error"].is_null() && static_cast<long>(parsed["error"]["error_code"]) == 15)
  {
    throw lib::common_error(__FILE__, __LINE__, 15, "Access denied.");
  }
}

void vk::messages::edit_chat(long chat_id, std::string_view new_title)
{
  network->request(append_url("messages.editChat"), {
    { "chat_id",      std::to_string(chat_id - 2000000000) },
    { "title",        new_title.data() },
    { "random_id",    "0"          },
    { "access_token", access_token },
    { "v",            api_v        }
   });
}

void vk::messages::set_chat_photo(std::string_view filename, std::string_view raw_server)
{
  std::string upload_url = static_cast<std::string>(parser->parse(raw_server)["response"]["upload_url"]);

  std::string raw_upload_response = network->upload("file", filename, static_cast<std::string>(upload_url));

  simdjson::dom::object upload_response = parser->parse(raw_upload_response);

  std::string raw_vk_response =
    network->request(append_url("messages.setChatPhoto"), {
      { "access_token",  access_token  },
      { "v",             api_v         },
      { "file",          static_cast<std::string>(upload_response["response"])}
    });
}






