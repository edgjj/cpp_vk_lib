#ifndef VK_LONG_POLL_API_H
#define VK_LONG_POLL_API_H

#include "config/loader.hpp"
#include "events/common_event.hpp"
#include "methods/groups.hpp"
#include "processing/task_queue.hpp"

#include "long_poll/data.hpp"


namespace vk {
namespace long_poll {
/*!
 * @brief Class to interact with long poll mechanism.
 */
class api {
public:
  explicit api(std::int64_t update_interval_ = 600);

  api(const api&) = delete;
  api(api&&) = delete;
  api& operator=(const api&) = delete;
  api& operator=(api&&) = delete;
  ~api() = default;

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
  events_t listen(data& lp_data, std::int8_t timeout = 60) const;
  template <typename _Execution_Policy>
  void on_event(std::string_view event_type, const event::common& event, _Execution_Policy executor) {
    if (event.on_type(event_type)) {
      queue(executor);
    }
  }
  /*!
   * @brief Push task to thread pool queue.
   */
  template <typename Function>
  void queue(Function&& function) {
    task_queue.queue(std::move(function));
  }
  /*!
   * @brief Pop and execute task from thread pool queue.
   */
  void run();

private:
  std::int64_t update_interval;
  std::int64_t group_id;
  /*!
   * @brief Class with group long poll methods.
   */
  method::groups groups;
  processing::task_queue task_queue;
};
} // namespace long_poll
} // namespace vk

#endif // VK_LONG_POLL_API_H
