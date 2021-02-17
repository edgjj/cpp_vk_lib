#ifndef VK_LONG_POLL_API_H
#define VK_LONG_POLL_API_H

#include "events/common_event.hpp"
#include "methods/groups.hpp"
#include "processing/thread_pool.hpp"


namespace vk {
/*!
 * @brief Wrapper for data returned by group long poll.
 */
struct vk_export long_poll_data {
  std::string key;
  std::string server;
  std::string ts;
};

/*!
 * @brief Class to interact with long poll mechanism.
 */
class vk_export long_poll_api {
public:
  disable_copy(long_poll_api)
  disable_move(long_poll_api)

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
   * @param Number of threads (default - maximum threads available on the computer).
   */
  void run(const std::int8_t num_threads = std::thread::hardware_concurrency());

private:
  std::string _group_id;
  /*!
   * @brief Class with group long poll methods.
   */
  vk::groups groups;
  processing::thread_pool thread_pool;
};
} // namespace vk

template <typename Function>
void vk::long_poll_api::queue(Function&& function)
{
  thread_pool.queue(function);
}

#endif // VK_LONG_POLL_API_H
