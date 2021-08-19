#include "vk/include/long_poll/long_poll.hpp"

#include "simdjson.h"
#include "spdlog/spdlog.h"
#include "vk/include/config/loader.hpp"
#include "vk/include/exception/error-inl.hpp"
#include "vk/include/methods/basic.hpp"
#include "vk/include/methods/utility/constructor.hpp"

namespace vk {

long_poll::long_poll(asio::io_context& io_context)
    : parser_(std::make_unique<simdjson::dom::parser>())
    , poll_payload_()
    , errc_()
    , io_context_(io_context)
    , started_(false)
{
    group_id_ = method::groups::get_by_id(errc_);
    if (errc_) { throw std::runtime_error("error retrieve group id"); }
    spdlog::info("long poll group: {}", group_id_);
}

long_poll::~long_poll() = default;

long_poll::poll_payload long_poll::server() const
{
    const std::string data = method::groups::get_long_poll_server(group_id_);
    const simdjson::dom::object server_object = parser_->parse(data)["response"];

    return {
        std::string(server_object["key"]),
        std::string(server_object["server"]),
        std::string(server_object["ts"]),
        std::chrono::seconds(std::time(nullptr)).count()
    };
}

std::vector<event::common> long_poll::listen(int8_t timeout)
{
    if (!started_) {
        poll_payload_ = server();
        started_ = true;
    }

    spdlog::info("long poll: ts {}, timeout {}", poll_payload_.ts, timeout);

    const std::string response = method::raw_constructor()
        .method(poll_payload_.server + "?")
        .param("act",   "a_check")
        .param("key",   poll_payload_.key)
        .param("ts",    poll_payload_.ts)
        .param("wait",  std::to_string(timeout))
        .perform_request();

    const simdjson::dom::object parsed_response = parser_->parse(response);

    if (parsed_response.begin().key() == "failed") {
        const int64_t code = parsed_response["failed"].get_int64();
        if (code == 2 || code == 3) {
            started_ = false;
            listen(timeout);
        }
    }

    std::vector<event::common> event_list;
    std::string ts(parsed_response["ts"]);

    for (auto update : parsed_response["updates"]) {
        event_list.emplace_back(ts, update);
    }

    poll_payload_.ts = std::move(ts);

    return event_list;
}

void long_poll::run()
{
    std::vector<std::thread> threads;
    const size_t num_workers = config::num_workers();
    for (size_t i = 0; i < num_workers; ++i) {
        threads.emplace_back([this] {
            io_context_.run();
        });
    }
    io_context_.run();
    for (auto& t : threads) {
        t.join();
    }
    io_context_.restart();
}

}// namespace vk