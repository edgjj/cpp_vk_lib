#ifndef VK_AT_PROGRAM_EXIT_H
#define VK_AT_PROGRAM_EXIT_H

#include "../dependencies/logger/logger.hpp"


namespace vk {
namespace processing {
/*!
 * @brief Finalizer.
 *
 * Please, use in main function.
 */
void set_program_finalizer() {
  std::atexit([]{
    // ...
  });
}
} // namespace processing
} // namespace vk

#endif // VK_AT_PROGRAM_EXIT_H
