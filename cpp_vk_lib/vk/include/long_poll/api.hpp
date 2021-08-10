#ifndef VK_LONG_POLL_API_HPP
#define VK_LONG_POLL_API_HPP

#include "runtime/include/misc/cppdefs.hpp"

#include "vk/include/events/common_event.hpp"
#include "vk/include/exception/error_code.hpp"
#include "vk/include/long_poll/data.hpp"

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
public:
    long_poll(asio::io_context& io_context);
    ~long_poll();

    VK_DISABLE_COPY_MOVE(long_poll)

    long_poll_data server() const;
    std::vector<event::common> listen(long_poll_data& data, int8_t timeout = 60) const;

    template <typename Task>
    void on_event(std::string_view event_type, const event::common& event, Task task);

    template <typename Executor>
    void enqueue(Executor executor);

    void run();

private:
    std::unique_ptr<simdjson::dom::parser> parser_;
    mutable error_code errc_;
    asio::io_context& io_context_;
    int64_t group_id_;
};

template <typename Task>
void long_poll::on_event(std::string_view event_type, const event::common& event, Task executor)
{
    if (event.on_type(event_type)) {
        enqueue(executor);
    }
}

template <typename Task>
void long_poll::enqueue(Task executor)
{
    asio::post(io_context_, executor);
}

}// namespace vk

#endif// VK_LONG_POLL_API_HPP
