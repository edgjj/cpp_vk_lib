#ifndef VK_LONG_POLL_API_HPP
#define VK_LONG_POLL_API_HPP

#include "runtime/include/processing/task_queue.hpp"

#include "vk/include/events/common_event.hpp"
#include "vk/include/long_poll/data.hpp"
#include "vk/include/methods/groups.hpp"

namespace vk {
namespace long_poll {
/*!
 * @brief Class to interact with long poll mechanism.
 */
class api
{
public:
    api(int64_t update_interval = 600);
    ~api() = default;

    VK_DISABLE_COPY_MOVE(api)

    using events_t = std::vector<std::unique_ptr<event::common>>;
    /*!
     * @brief Get long poll server.
     * @return parsed data.
     */
    data server() const;
    /*!
     * @brief Try get updates.
     * @return vector with `common` update objects.
     *
     * In the case, when no updates were returned, the request is executed again.
     */
    events_t listen(data& lp_data, int8_t timeout = 60) const;

    template <typename ExecutionPolicy>
    void on_event(std::string_view event_type, const event::common& event, ExecutionPolicy executor)
    {
        if (event.on_type(event_type))
        {
            queue(executor);
        }
    }
    /*!
     * @brief Push task to thread pool queue.
     */
    template <typename Function>
    void queue(Function&& function)
    {
        m_task_queue.push_void_task(std::move(function));
    }
    /*!
     * @brief Pop and execute task from thread pool queue.
     */
    void run();

private:
    std::shared_ptr<simdjson::dom::parser> m_parser;
    error_code m_stored_error;
    /*!
     * @brief Class with group long poll methods.
     */
    runtime::processing::task_queue m_task_queue;
    mutable method::raw_constructor m_raw_method;
    method::groups m_groups;
    int64_t m_group_id;
    int64_t m_update_interval;
};

}// namespace long_poll
}// namespace vk

#endif// VK_LONG_POLL_API_HPP
