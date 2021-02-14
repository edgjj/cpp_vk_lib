#ifndef VK_COMMON_EVENT_H
#define VK_COMMON_EVENT_H

#include "events/message_new.hpp"
#include "events/wall_post_new.hpp"
#include "events/wall_reply_new.hpp"


namespace simdjson {
namespace dom {
class object;
} // namespace dom
} // namespace simdjson

namespace vk {
namespace event {
/*!
 * @brief Temporary update container.
 */
class vk_export common {
public:
  common(std::string_view ts, simdjson::dom::object&& event);

  /*!
   * @brief Get generated update type.
   */
  std::string type() const noexcept;
  /*!
   * @brief Get ts of current update.
   */
  std::string ts()   const noexcept;
  /*!
   * @brief Get raw json packed to std::string.
   */
  std::string dump() const noexcept;

  /*!
   * @brief Check if event matches @param type.
   * @param type
   */
  bool on_type(std::string_view type) const noexcept;
  /*!
   * @brief Try generate `message_new` update.
   */
  message_new get_message_event() const;
  /*!
   * @brief Try generate `wall_post_new` update.
   */
  wall_post_new get_wall_post_event() const;
  /*!
   * @brief Try generate `wall_reply_new` update.
   */
  wall_reply_new get_wall_reply_event() const;

private:
  std::string _ts;
  std::string _update_type;
  std::unique_ptr<simdjson::dom::object> _event;
};
} // namespace event
} // namespace vk

#endif // VK_COMMON_EVENT_H
