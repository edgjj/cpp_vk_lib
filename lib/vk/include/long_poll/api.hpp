#ifndef VK_LONG_POLL_API_HPP
#define VK_LONG_POLL_API_HPP

#include "runtime/include/processing/task_queue.hpp"

#include "vk/include/events/common_event.hpp"
#include "vk/include/exception/error_code.hpp"
#include "vk/include/long_poll/data.hpp"

namespace simdjson {
namespace dom {
class object;
class parser;
}// namespace dom
}// namespace simdjson

namespace vk {
/*!
 * @brief Class to interact with long poll mechanism.
 */
class long_poll
{
public:
    long_poll();

    ~long_poll();

    VK_DISABLE_COPY_MOVE(long_poll)

    long_poll_data server() const;
    std::vector<event::common> listen(long_poll_data& data, int8_t timeout = 60) const;

    template <typename Executor>
    void on_event(std::string_view event_type, const event::common& event, Executor&& executor);

    template <typename Executor>
    void enqueue(Executor&& executor);

    void run();

private:
    std::unique_ptr<simdjson::dom::parser> m_parser;
    mutable error_code m_stored_error;
    runtime::processing::task_queue m_task_queue;
    int64_t m_group_id;
};

}// namespace vk

template <typename Executor>
void vk::long_poll::on_event(std::string_view event_type, const event::common& event, Executor&& executor)
{
    if (event.on_type(event_type)) {
        enqueue(executor);
    }
}

template <typename Executor>
void vk::long_poll::enqueue(Executor&& executor)
{
    m_task_queue.push_void_task(std::forward<Executor>(executor));
}

#endif// VK_LONG_POLL_API_HPP
