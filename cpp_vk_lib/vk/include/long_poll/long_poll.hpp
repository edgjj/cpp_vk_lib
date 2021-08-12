#ifndef VK_LONG_POLL_API_HPP
#define VK_LONG_POLL_API_HPP

#include "runtime/include/misc/cppdefs.hpp"

#include "vk/include/events/common_event.hpp"
#include "vk/include/exception/error_code.hpp"

#include "asio/io_context.hpp"
#include "asio/post.hpp"

#include <vector>

namespace simdjson::dom {
class object;
class parser;
}// namespace simdjson::dom

namespace vk {
/*!
 * @brief Class to interact with long poll mechanism.
 */
class long_poll
{
    struct poll_payload
    {
        std::string key;
        std::string server;
        std::string ts;
        time_t update_time = 0;
    };

public:
    long_poll(asio::io_context& io_context);
    ~long_poll();

    VK_DISABLE_COPY_MOVE(long_poll)

    std::vector<event::common> listen(int8_t timeout = 60) const;

    template <typename Task>
    void on_event(std::string_view event_type, const event::common& event, Task task);

    void run();

private:
    poll_payload server() const;

    template <typename Executor>
    void enqueue(Executor executor);

    std::unique_ptr<simdjson::dom::parser> parser_;
    mutable poll_payload poll_payload_;
    mutable error_code errc_;
    asio::io_context& io_context_;
    int64_t group_id_;
};

template <typename Task>
void long_poll::on_event(std::string_view event_type, const event::common& event, Task task)
{
    if (event.on_type(event_type)) {
        enqueue(task);
    }
}

template <typename Task>
void long_poll::enqueue(Task executor)
{
    asio::post(io_context_, executor);
}

}// namespace vk

#endif// VK_LONG_POLL_API_HPP