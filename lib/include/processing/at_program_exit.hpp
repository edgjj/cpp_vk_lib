#ifndef VK_AT_PROGRAM_EXIT_H
#define VK_AT_PROGRAM_EXIT_H

#include "config/loader.hpp"
#include "../dependencies/logger/logger.hpp"


namespace vk {
namespace processing {
/*!
 * @brief Global instances deleter.
 *
 * Please, use in main function.
 */
void set_at_exit_deallocator() {
  std::atexit([]{
    config::deallocate();
    logger(logflag::info | logflag::yellow) << "deallocating config instance...";
  });
}
} // namespace processing
} // namespace vk

#endif // VK_AT_PROGRAM_EXIT_H
