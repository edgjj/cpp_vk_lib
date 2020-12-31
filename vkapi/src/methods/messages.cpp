#include <simdjson.h>

#include "vkapi/include/lib/common_error.hpp"
#include "vkapi/include/lib/network.hpp"
#include "vkapi/include/methods/messages.hpp"

static void append_attachments(std::map<std::string, std::string>& parameters, const vk::attachment::attachment_list& list)
{
  std::string attachments;
  for (auto&& attachment : list)
  {
    attachments += attachment->value() + ',';
  }
  parameters.insert({{"attachment", attachments}});
}

void vk::messages::send(std::int64_t peer_id, std::string_view text, const vk::attachment::attachment_list& list) const
{
  std::map<std::string, std::string> parameters = {
    { "message",      text.data()  },
    { "peer_id",      std::to_string(peer_id) },
    { "random_id",    "0"          },
    { "access_token", access_token },
    { "v",            api_v        },
    { "disable_mentions", "1"      }
  };
  if (not list.empty())
  {
    append_attachments(parameters, list);
  }
  network->request(append_url("messages.send"), parameters);
}

void vk::messages::send(std::int64_t peer_id, std::string_view text) const
{
  send(peer_id, text, {});
}

void vk::messages::remove_chat_user(std::int64_t chat_id, std::int64_t user_id) const
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

  if (not parsed["error"].is_null() && static_cast<std::int64_t>(parsed["error"]["error_code"]) == 100)
  {
    throw vk::common_error(__FILE__, __LINE__, 100, "Can't kick this user/group.");
  }
  if (not parsed["error"].is_null() && static_cast<std::int64_t>(parsed["error"]["error_code"]) == 15)
  {
    throw vk::common_error(__FILE__, __LINE__, 15, "Access denied.");
  }
}

void vk::messages::edit_chat(std::int64_t chat_id, std::string_view new_title) const
{
  network->request(append_url("messages.editChat"), {
    { "chat_id",      std::to_string(chat_id - 2000000000) },
    { "title",        new_title.data() },
    { "random_id",    "0"          },
    { "access_token", access_token },
    { "v",            api_v        }
   });
}

void vk::messages::set_chat_photo(std::string_view filename, std::string_view raw_server) const
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
