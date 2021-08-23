#ifndef VK_LONG_POLL_API_HPP
#define VK_LONG_POLL_API_HPP

#include "asio/io_context.hpp"
#include "asio/post.hpp"
#include "cpp_vk_lib/runtime/misc/cppdefs.hpp"
#include "cpp_vk_lib/vk/error/error_code.hpp"
#include "cpp_vk_lib/vk/events/common.hpp"

#include <vector>

namespace simdjson::dom {
class object;
class parser;
}// namespace simdjson::dom

namespace vk {
/*!
 * \brief Event queue that implements group long polling.
 */
class long_poll
{
    /*!
     * groups.getLongPollServer wrapper
     */
    struct poll_payload
    {
        std::string key;
        std::string server;
        std::string ts;
    };

public:
    /*!
     * Get and setup group_id by token.
     *
     * \throw exception::access_error if group_id retrieving failed
     */
    long_poll(asio::io_context& io_context);
    ~long_poll();

    VK_DISABLE_COPY_MOVE(long_poll)
    /*!
     * Execute "listening" with maximum delay = timeout.
     *
     * At first start, new Long Poll server retrieved.
     *
     * If Long Poll returned error with code 2 or 3, new server is retrieved.
     *
     * \return raw event list
     */
    std::vector<event::common> listen(int8_t timeout = 60);
    /*!
     * Setup action on selected event type.
     *
     * \note If invalid event type provided, nothing will happen.
     */
    template <typename Executor>
    void on_event(
        std::string_view event_type,
        const event::common& event,
        Executor executor);
    /*!
     * Execute all existing tasks.
     *
     * After all tasks are completed, the queue returns to its original state.
     */
    void run();

private:
    /*!
     * Get new long poll server.
     *
     * \note All checks is the responsibility of the caller.
     */
    poll_payload server() const;
    /*!
     * Push task to event queue.
     */
    template <typename Executor>
    void enqueue(Executor executor);

    std::unique_ptr<simdjson::dom::parser> parser_;
    poll_payload poll_payload_;
    error_code errc_;
    asio::io_context& io_context_;
    int64_t group_id_;
    bool started_;
};

template <typename Executor>
void long_poll::on_event(
    std::string_view event_type,
    const event::common& event,
    Executor executor)
{
    if (event.on_type(event_type)) {
        enqueue(executor);
    }
}

template <typename Executor>
void long_poll::enqueue(Executor executor)
{
    asio::post(io_context_, executor);
}

}// namespace vk

#endif// VK_LONG_POLL_API_HPP
