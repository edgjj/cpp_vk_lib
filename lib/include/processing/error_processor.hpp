#ifndef VK_ERROR_HANDLER_H
#define VK_ERROR_HANDLER_H

#include "config/loader.hpp"
#include "processing/exception.hpp"
#include "../dependencies/logger/logger.hpp"


namespace vk {
namespace processing {
/*!
 * @brief Log information about error and throw it.
 */
template <typename vk_exception_t>
void error_log_and_throw(std::string_view label, vk_exception_t e) {
  logger(vk::config::error_logpath(), logflag::error) << label << ": " << e.what();
  throw e;
}
/*!
 * @brief Log information about error without throwing.
 */
template <typename vk_exception_t>
void error_log_only(std::string_view label, vk_exception_t e) {
  logger(vk::config::error_logpath(), logflag::error) << label << ": " << e.what();
}
} // namespace processing
} // namespace vk

#endif // VK_ERROR_HANDLER_H
