#ifndef VK_EXCEPTION_H
#define VK_EXCEPTION_H

#include "misc/backtrace.hpp"


namespace vk {
namespace exception {
class vk_export common_exception : public std::exception {
protected:
    explicit common_exception(const char* what_arg, unsigned int line)
        : error(what_arg)
    {
        backtrace_view{line};
    }
    virtual const char* what() const noexcept override {
        return error.what();
    }
    std::string create(const std::string& ename, const int id) const {
        return "[vk.exception." + ename + '.' + std::to_string(id) + "]: ";
    }

private:
    std::runtime_error error;
};

#define GENERATE_EXCEPTION_CLASS(EXCEPTION) \
    class vk_export EXCEPTION : public common_exception { \
    public: \
        explicit EXCEPTION(int id, const char* what_arg, unsigned int line) \
            : common_exception(std::string(create(#EXCEPTION, id) + what_arg).c_str(), line) \
        { } \
    }; \

GENERATE_EXCEPTION_CLASS(upload_error)
GENERATE_EXCEPTION_CLASS(access_error)
GENERATE_EXCEPTION_CLASS(invalid_parameter_error)
} // namespace exception
} // namespace vk

#define VK_THROW(EXCEPTION, ID, MESSAGE) \
    throw EXCEPTION(ID, MESSAGE, __LINE__)

#undef GENERATE_EXCEPTION_CLASS

#endif // VK_EXCEPTION_H
