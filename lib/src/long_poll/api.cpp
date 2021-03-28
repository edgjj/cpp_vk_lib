#include "spdlog/spdlog.h"

#include "simdjson.h"

#include "long_poll/api.hpp"


vk::long_poll::api::api(std::int64_t update_interval_)
  : update_interval(update_interval_), group_id(), groups(), task_queue()
{
  group_id = groups.get_by_id();
  spdlog::info("long polling started");
  spdlog::info("group id: {}", group_id);
}

vk::long_poll::data vk::long_poll::api::server() const {
  simdjson::dom::object server(groups.get_long_poll_server(group_id));
  return {
    server["key"].get_c_str().take_value(),
    server["server"].get_c_str().take_value(),
    server["ts"].get_c_str().take_value()
  };
}

static simdjson::dom::object get_updates(const vk::long_poll::data& data, std::size_t timeout) {
  static vk::network_client net_client;
  static simdjson::dom::parser parser;

  return parser.parse(
    net_client.request(data.server + '?', {
      {"act",     "a_check"},
      {"key",     data.key},
      {"ts",      data.ts},
      {"wait",    std::to_string(timeout)}
    })
  );
}

vk::long_poll::api::events_t vk::long_poll::api::listen(vk::long_poll::data& data, std::int8_t timeout) const {
  events_t event_list;
  simdjson::dom::object updates_json(get_updates(data, timeout));
  simdjson::dom::array updates(updates_json["updates"].get_array());
  if (std::time(nullptr) % update_interval == 0)
    data = server();

  for (simdjson::dom::element&& update : updates) {
    event_list.push_back(std::make_unique<vk::event::common>(
      updates_json["ts"].get_string(),
      std::move(update)
    ));
  }
  data.ts = updates_json["ts"].get_c_str();
  return event_list;
}

void vk::long_poll::api::run() {
  task_queue.start();
}
