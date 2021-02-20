#ifndef VK_ERROR_HANDLER_H
#define VK_ERROR_HANDLER_H

#include "config/loader.hpp"
#include "processing/exception.hpp"
#include "../dependencies/logger/logger.hpp"


namespace vk {
namespace processing {
/*!
 * @brief Write information about error to logfile and throw it.
 */
template <typename vk_exception_t>
void process_error(std::string_view label, vk_exception_t e) {
  logger(vk::config::error_logpath(), logflag::error) << label << ": " << e.what();
  throw e;
}

} // namespace processing
} // namespace vk

#endif // VK_ERROR_HANDLER_H
