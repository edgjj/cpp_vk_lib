#include <simdjson.h>

#include "vkapi/include/lib/network.hpp"
#include "vkapi/include/document/common_document.hpp"

static void photos_search(vk::attachment::attachment_list& documents, const simdjson::dom::array& items)
{
  for (std::size_t i = 0; i < items.size() && i < 10; i++)
  {
    std::size_t index = rand() % items.size();
    documents.push_back(std::make_shared<vk::attachment::photo_attachment>(
      static_cast<long>(items.at(index)["owner_id"]),
      static_cast<long>(items.at(index)["id"])
    ));
  }
}

static void video_search(vk::attachment::attachment_list& documents, const simdjson::dom::array& items)
{
  for (std::size_t i = 0; i < items.size() && i < 10; i++)
  {
    std::size_t index = rand() % items.size();
    documents.push_back(std::make_shared<vk::attachment::video_attachment>(
      static_cast<long>(items.at(index)["owner_id"]),
      static_cast<long>(items.at(index)["id"])
    ));
  }
}

static void docs_search(vk::attachment::attachment_list& documents, const simdjson::dom::array& items)
{
  for (std::size_t i = 0; i < items.size() && i < 10; i++)
  {
    std::size_t index = rand() % items.size();
    documents.push_back(std::make_shared<vk::attachment::document_attachment>(
      static_cast<long>(items.at(index)["owner_id"]),
      static_cast<long>(items.at(index)["id"]),
      static_cast<std::string_view>(items.at(index)["url"]) ///< static_cast to std::string causes UB!
    ));
  }
}

vk::attachment::attachment_list vk::document::common::common_search(std::string_view type, std::string_view query, long count) const
{
  vk::attachment::attachment_list documents;

  std::string raw_json =
  network->request(append_url(type), {
    {"q",             query.data()  },
    {"access_token",  user_token    },
    {"v",             api_v         },
    {"count",         std::to_string(count)}
  });

  simdjson::dom::array items = parser->parse(raw_json)["response"]["items"].get_array();

  if (items.size() == 0) return documents;

  if (type == "photos.search") photos_search(documents, items);
  if (type == "video.search")  video_search(documents, items);
  if (type == "docs.search")   docs_search(documents, items);

  return documents;
}
