#include "vk/include/long_poll/api.hpp"

#include "vk/include/config/loader.hpp"
#include "vk/include/methods/basic.hpp"
#include "vk/include/methods/utility/constructor.hpp"
#include "vk/include/exception/error-inl.hpp"

#include "simdjson.h"
#include "spdlog/spdlog.h"

vk::long_poll::long_poll(asio::io_context& io_context)
    : m_parser(std::make_unique<simdjson::dom::parser>())
    , m_stored_error()
    , m_io_context(io_context)
{
    m_group_id = vk::method::groups::get_by_id(m_stored_error);
    if (m_stored_error) { throw std::runtime_error("error retrieve group id"); }

    spdlog::info("long poll group: {}", m_group_id);
}

vk::long_poll::~long_poll() = default;

vk::long_poll_data vk::long_poll::server() const
{
    const std::string data = method::groups::get_long_poll_server(m_group_id);
    const simdjson::dom::object server_object = m_parser->parse(data)["response"];
    if (m_stored_error) { throw std::runtime_error("Failed to get long poll server"); }

    return {
        std::string(server_object["key"]),
        std::string(server_object["server"]),
        std::string(server_object["ts"])
    };
}

std::vector<vk::event::common> vk::long_poll::listen(vk::long_poll_data& data, int8_t timeout) const
{
    spdlog::info("long poll: ts {} timeout {}", data.ts, timeout);

    const std::string response = method::raw_constructor()
        .method(data.server + "?")
        .param("act", "a_check")
        .param("key", data.key)
        .param("ts", data.ts)
        .param("wait", std::to_string(timeout))
        .perform_request();

    simdjson::dom::object parsed_response = m_parser->parse(response);

    std::vector<vk::event::common> event_list;
    std::string ts(parsed_response["ts"]);

    for (auto update : parsed_response["updates"]) {
        event_list.emplace_back(ts, update);
    }

    data.ts = std::move(ts);

    return event_list;
}

void vk::long_poll::run()
{
    std::vector<std::thread> threads;
    for (size_t i = 0; i < vk::config::num_workers(); ++i) {
        threads.emplace_back([this] { m_io_context.run(); });
    }
    m_io_context.run();
    for (auto& t : threads) {
        t.join();
    }
    threads.clear();
    m_io_context.restart();
}
