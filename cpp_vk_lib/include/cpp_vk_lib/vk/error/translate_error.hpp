#ifndef VK_ERROR_TRANSLATE_ERROR_HPP
#define VK_ERROR_TRANSLATE_ERROR_HPP

#include <cstddef>
#include <unordered_map>

namespace vk::exception {
/*!
 * \return Detailed VK error description by its code
 */
const char* translate_error(size_t error_code);

}// namespace vk::exception

#endif// VK_ERROR_TRANSLATE_ERROR_HPP
