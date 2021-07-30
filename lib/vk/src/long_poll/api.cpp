#include "vk/include/long_poll/api.hpp"

#include "vk/include/config/loader.hpp"

#include "simdjson.h"
#include "spdlog/spdlog.h"

vk::long_poll::api::api(int64_t update_interval)
    : m_parser(std::make_shared<simdjson::dom::parser>())
    , m_task_queue(vk::config::num_workers())
    , m_raw_method()
    , m_groups()
    , m_group_id(m_groups.get_by_id())
    , m_update_interval(update_interval)
{
    spdlog::info("long poll group: - {}", m_group_id);
}

vk::long_poll::data vk::long_poll::api::server() const
{
    const simdjson::dom::object server_object = m_groups.get_long_poll_server(m_group_id);

    const std::string key = server_object["key"].get_c_str().take_value();
    const std::string server = server_object["server"].get_c_str().take_value();
    const std::string ts = server_object["ts"].get_c_str().take_value();

    return { key, server, ts };
}

vk::long_poll::api::events_t vk::long_poll::api::listen(vk::long_poll::data& data, int8_t timeout) const
{
    spdlog::info("long poll: ts {} timeout {}", data.ts, timeout);

    events_t event_list;

    const std::string response = m_raw_method
        .method(data.server + "?")
        .param("act", "a_check")
        .param("key", data.key)
        .param("ts", data.ts)
        .param("wait", std::to_string(timeout))
        .perform_request();

    const simdjson::dom::object parsed_response = m_parser->parse(response);

    if (std::time(nullptr) % m_update_interval == 0) {
        data = server();
    }

    for (auto&& update : parsed_response["updates"].get_array()) {
        event_list.push_back(std::make_unique<vk::event::common>(parsed_response["ts"].get_string(), std::move(update)));
    }

    data.ts = parsed_response["ts"].get_c_str().take_value();
    return event_list;
}

void vk::long_poll::api::run()
{
    m_task_queue.start();
    m_task_queue.wait_for_completion();
}
