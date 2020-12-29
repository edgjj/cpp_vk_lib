#include <simdjson.h>

#include "vkapi/include/lib/network.hpp"
#include "vkapi/include/methods/docs.hpp"

vk::attachment::attachment_list vk::docs::search(std::string_view query, long count)
{
  return common_search("docs.search", query, count);
}

std::string vk::docs::get_upload_server(long group_id)
{
  return network->request(append_url("docs.getUploadServer"), {
    {"access_token",  user_token    },
    {"v",             api_v         },
    {"group_id",      std::to_string(group_id)}
  });
}

std::shared_ptr<vk::attachment::document_attachment> vk::docs::save([[maybe_unused]] std::string_view file, [[maybe_unused]] std::string_view raw_server)
{
//  simdjson::dom::object upload_server = parser->parse(raw_server);

  // ...
  return std::make_shared<vk::attachment::document_attachment>(0, 0, "");
}
