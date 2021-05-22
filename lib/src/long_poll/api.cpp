#include "long_poll/api.hpp"

#include "config/loader.hpp"
#include "simdjson.h"
#include "spdlog/spdlog.h"

vk::long_poll::api::api(std::int64_t update_interval)
  : m_parser(std::make_shared<simdjson::dom::parser>())
  , m_task_queue(vk::config::num_workers())
  , m_raw_method()
  , m_groups()
  , m_group_id(m_groups.get_by_id())
  , m_update_interval(update_interval)
{
    spdlog::info("Long poll: group id - {}", m_group_id);
}

vk::long_poll::data vk::long_poll::api::server() const
{
    simdjson::dom::object server_object = m_groups.get_long_poll_server(m_group_id);

    std::string key = server_object["key"].get_c_str().take_value();
    std::string server = server_object["server"].get_c_str().take_value();
    std::string ts = server_object["ts"].get_c_str().take_value();

    return { key, server, ts };
}

vk::long_poll::api::events_t vk::long_poll::api::listen(vk::long_poll::data& data, std::int8_t timeout) const
{
    events_t event_list;

    std::string response = m_raw_method
        .method(data.server + "?")
        .param("act", "a_check")
        .param("key", data.key)
        .param("ts", data.ts)
        .param("wait", std::to_string(timeout))
        .execute();

    simdjson::dom::object parsed_response = m_parser->parse(response);

    simdjson::dom::array updates = parsed_response["updates"].get_array();

    if (std::time(nullptr) % m_update_interval == 0)
    {
        data = server();
    }

    for (simdjson::dom::element&& update : updates)
    {
        event_list.push_back(std::make_unique<vk::event::common>(parsed_response["ts"].get_string(), std::move(update)));
    }

    data.ts = parsed_response["ts"].get_c_str();
    return event_list;
}

void vk::long_poll::api::run()
{
    m_task_queue.start();
    m_task_queue.wait_for_completion();
}
