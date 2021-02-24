#include "simdjson.h"

#include "document/common_document.hpp"


vk::document::common::common()
  : parser(std::make_unique<simdjson::dom::parser>())
{ }

vk::document::common::~common() = default;

template <typename function>
static void search_attachments(const simdjson::dom::array& items, function&& fun) {
  for (std::size_t i = 0; i < items.size() && i < 10; i++) {
    std::size_t index = rand() % items.size();
    fun(index);
  }
}

vk::attachment::attachments_t vk::document::common::common_search(std::string_view method, std::string_view query, std::int64_t count) {
  vk::attachment::attachments_t documents;
  std::string raw_json = method_util.call(method, method_util.user_args({{"q", query.data()}, {"count", std::to_string(count)}}));
  simdjson::dom::array items = parser->parse(raw_json)["response"]["items"].get_array();
  documents.reserve(items.size());

  if (items.size() == 0) { return documents; }

  if (method == "photos.search") search_attachments(items, [&documents, &items](std::size_t index){
    documents.push_back(std::make_shared<vk::attachment::photo>(
      items.at(index)["owner_id"].get_int64(),
      items.at(index)["id"].get_int64()
    ));
  });
  else if (method == "video.search") search_attachments(items, [&documents, &items](std::size_t index){
    documents.push_back(std::make_shared<vk::attachment::video>(
      items.at(index)["owner_id"].get_int64(),
      items.at(index)["id"].get_int64()
    ));
  });
  else if (method == "docs.search") search_attachments(items, [&documents, &items](std::size_t index){
    documents.push_back(std::make_shared<vk::attachment::document>(
      items.at(index)["owner_id"].get_int64(),
      items.at(index)["id"].get_int64(),
      items.at(index)["url"].get_string()
    ));
  });

  return documents;
}

simdjson::dom::object vk::document::common::common_upload(
  std::string_view filename,
  std::string_view server,
  std::string_view field_name)
{
  return
  parser->parse(
    net_client.upload(
      field_name, filename,
      parser->parse(server)["response"]["upload_url"].get_string()
    )
  );
}
