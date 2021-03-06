#include "simdjson.h"

#include "long_poll/long_poll_api.hpp"

#include "../../dependencies/logger/logger.hpp"


vk::long_poll_api::long_poll_api() {
  group_id = groups.get_by_id();
  logger(logflag::info) << "long polling started";
  logger(logflag::info) << "group id: " << group_id;
}

vk::long_poll_data vk::long_poll_api::server() const {
  simdjson::dom::object server(groups.get_long_poll_server(group_id));
  return {
    server["key"].get_c_str().take_value(),
    server["server"].get_c_str().take_value(),
    server["ts"].get_c_str().take_value()
  };
}

static simdjson::dom::object get_updates(const vk::long_poll_data& data, std::size_t timeout) {
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

vk::long_poll_api::events_t vk::long_poll_api::listen(long_poll_data& data, std::int8_t timeout) const {
  events_t event_list;
  simdjson::dom::object raw_updates(get_updates(data, timeout));
  simdjson::dom::array raw_updates_array(raw_updates["updates"].get_array());
  if (raw_updates_array.size() == 0)
    data = server();

  for (simdjson::dom::element&& update : raw_updates_array) {
    event_list.push_back(std::make_unique<vk::event::common>(
      raw_updates["ts"].get_string(),
      std::move(update)
    ));
  }
  data.ts = raw_updates["ts"].get_c_str();
  return event_list;
}

void vk::long_poll_api::run() {
  task_queue.start();
}
