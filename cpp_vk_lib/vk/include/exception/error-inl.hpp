#ifndef VK_EXCEPTION_ERROR_INL_HPP
#define VK_EXCEPTION_ERROR_INL_HPP

#include <unordered_map>
#include <cstddef>

namespace vk {
namespace exception {

enum class error_type : size_t
{
    upload_error,
    access_error,
    invalid_parameter_error,
    runtime_error,
};

const char* translate_error(size_t error_code);
void process_error(size_t error_code);
void process_error(const char* message, error_type err_type);

} // namespace exception
} // namespace vk

#endif // VK_EXCEPTION_ERROR_INL_HPP
