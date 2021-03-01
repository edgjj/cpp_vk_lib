#ifndef VK_LONG_POLL_API_H
#define VK_LONG_POLL_API_H

#include "config/loader.hpp"
#include "events/common_event.hpp"
#include "methods/groups.hpp"
#include "processing/task_queue.hpp"

#include "long_poll/long_poll_data.hpp"


namespace vk {
/*!
 * @brief Class to interact with long poll mechanism.
 */
class vk_export long_poll_api {
public:
  long_poll_api(const long_poll_api&) = delete;
  long_poll_api(long_poll_api&&) = delete;
  long_poll_api& operator=(const long_poll_api&) = delete;
  long_poll_api& operator=(long_poll_api&&) = delete;
  using events_t = std::vector<std::unique_ptr<event::common>>;

  explicit long_poll_api();
  /*!
   * @brief Get long poll server.
   * @return parsed data.
   */
  long_poll_data server();
  /*!
   * @brief Try get updates.
   * @return vector with `common` update objects.
   *
   * In the case, when no updates were returned, the request is executed again.
   */
  events_t listen(long_poll_data& data, std::int8_t timeout = 60);

  /*!
   * @brief Push task to thread pool queue.
   */
  template <typename Function>
  void queue(Function&& function);
  /*!
   * @brief Pop and execute task from thread pool queue.
   */
  void run();

private:
  std::string _group_id;
  /*!
   * @brief Class with group long poll methods.
   */
  method::groups groups;
  processing::task_queue task_queue;
};
} // namespace vk

template <typename Function>
void vk::long_poll_api::queue(Function&& function) {
  task_queue.queue(function);
}

#endif // VK_LONG_POLL_API_H
