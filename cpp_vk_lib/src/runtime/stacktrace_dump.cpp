#include "cpp_vk_lib/runtime/stacktrace_dump.hpp"

#include "spdlog/spdlog.h"

#if defined(__ANDROID__)
#   include <sstream>
#   include <iomanip>
#   include <android/log.h>
#   include <unwind.h>
#   include <dlfcn.h>
#elif defined(__FreeBSD__) || defined(__linux__) || defined(__APPLE__)
#   include <cxxabi.h>
#   include <execinfo.h>
#else
#   error Unknown platform
#endif

#if defined(__ANDROID__)
struct backtrace_state
{
    void** current;
    void** end;
};

static _Unwind_Reason_Code unwind_callback(struct _Unwind_Context* context, void* arg)
{
    backtrace_state* state = static_cast<backtrace_state*>(arg);
    uintptr_t pc = _Unwind_GetIP(context);
    if (pc) {
        if (state->current == state->end) {
            return _URC_END_OF_STACK;
        } else {
            *state->current++ = reinterpret_cast<void*>(pc);
        }
    }
    return _URC_NO_REASON;
}

static size_t capture_stacktrace(void** buffer, size_t max)
{
    backtrace_state state { buffer, buffer + max };
    _Unwind_Backtrace(unwind_callback, &state);
    return state.current - buffer;
}

static void android_stacktrace_dump_implementation()
{
    const size_t max_stacktrace_records = 25;
    void* buffer[max_stacktrace_records];
    std::ostringstream ostream;

    const size_t stacktrace_size = capture_stacktrace(buffer, max_stacktrace_records);
    for (size_t i = 0; i < stacktrace_size; ++i) {
        const void* address = buffer[i];
        const char* symbol = "";
        Dl_info info;
        if (dladdr(address, &info) && info.dli_sname) {
            symbol = info.dli_sname;
        }
        ostream << "  " << std::setw(2) << ": " << address << " " << symbol << std::endl;
    }
    spdlog::critical("{}", ostream.str());
}
#elif defined(__FreeBSD__) || defined(__linux__) || defined(__APPLE__)
static void unix_stacktrace_dump_implementation()
{
    const size_t max_stacktrace_records = 25;
    void* address_list[max_stacktrace_records];
    int addresses_got = backtrace(address_list, sizeof(address_list) / sizeof(void*));
    if (addresses_got == 0) {
        spdlog::critical("  empty stack trace, exiting...");
        return;
    }
    char** symbol_list = backtrace_symbols(address_list, addresses_got);
    size_t maxframes = 256;
    char* funcname = static_cast<char*>(malloc(maxframes));
    for (int i = 1; i < addresses_got; ++i) {
        char* begin_name = 0, *begin_offset = 0, *end_offset = 0;
        for (char* symbol = symbol_list[i]; *symbol; ++symbol) {
            if (*symbol == '(') {
                begin_name = symbol;
            } else if (*symbol == '+') {
                begin_offset = symbol;
            } else if (*symbol == ')' && begin_offset) {
                end_offset = symbol;
                break;
            }
        }
        if (begin_name && begin_offset && end_offset && begin_name < begin_offset) {
            *begin_name++ = '\0';
            *begin_offset++ = '\0';
            *end_offset = '\0';
            int status = 0;
            char* demangled = abi::__cxa_demangle(begin_name, funcname, &maxframes, &status);
            if (status == 0) {
                funcname = demangled;
                spdlog::critical("  {}: {}+{}", symbol_list[i], funcname, begin_offset);
            } else {
                spdlog::critical("  {}: {}()+{}", symbol_list[i], begin_name, begin_offset);
            }
        } else {
            spdlog::critical("  {}", symbol_list[i]);
        }
    }
    free(funcname);
    free(symbol_list);
}
#endif

//#if defined(__unix__ ) || defined(__unix) || \
//   (defined(__APPLE__) && defined(__MACH__))
//static void unix_stacktrace_dump_implementation()
//{
//    const size_t max_stacktrace_records = 25;
//    void* address_list[max_stacktrace_records];
//    int addresses_got = backtrace(address_list, sizeof(address_list) / sizeof(void*));
//    if (addresses_got == 0) {
//        spdlog::critical("  empty stack trace, exiting...");
//        return;
//    }
//    char** symbol_list = backtrace_symbols(address_list, addresses_got);
//    size_t maxframes = 256;
//    char* funcname = static_cast<char*>(malloc(maxframes));
//    for (int i = 1; i < addresses_got; ++i) {
//        char* begin_name = 0, *begin_offset = 0, *end_offset = 0;
//        for (char* symbol = symbol_list[i]; *symbol; ++symbol) {
//            if (*symbol == '(') {
//                begin_name = symbol;
//            } else if (*symbol == '+') {
//                begin_offset = symbol;
//            } else if (*symbol == ')' && begin_offset) {
//                end_offset = symbol;
//                break;
//            }
//        }
//        if (begin_name && begin_offset && end_offset && begin_name < begin_offset) {
//            *begin_name++ = '\0';
//            *begin_offset++ = '\0';
//            *end_offset = '\0';
//            int status = 0;
//            char* demangled = abi::__cxa_demangle(begin_name, funcname, &maxframes, &status);
//            if (status == 0) {
//                funcname = demangled;
//                spdlog::critical("  {}: {}+{}", symbol_list[i], funcname, begin_offset);
//            } else {
//                spdlog::critical("  {}: {}()+{}", symbol_list[i], begin_name, begin_offset);
//            }
//        } else {
//            spdlog::critical("  {}", symbol_list[i]);
//        }
//    }
//    free(funcname);
//    free(symbol_list);
//}
//#endif // defined __unix__ || defined __APPLE__

//#if  defined(__ANDROID__)
//struct backtrace_state
//{
//    void** current;
//    void** end;
//};

//static _Unwind_Reason_Code unwind_callback(struct _Unwind_Context* context, void* arg)
//{
//    backtrace_state* state = static_cast<backtrace_state*>(arg);
//    uintptr_t pc = _Unwind_GetIP(context);
//    if (pc) {
//        if (state->current == state->end) {
//            return _URC_END_OF_STACK;
//        } else {
//            *state->current++ = reinterpret_cast<void*>(pc);
//        }
//    }
//    return _URC_NO_REASON;
//}

//static size_t capture_stacktrace(void** buffer, size_t max)
//{
//    backtrace_state state { buffer, buffer + max };
//    _Unwind_Backtrace(unwind_callback, &state);
//    return state.current - buffer;
//}

//static void android_stacktrace_dump_implementation()
//{
//    const size_t max_stacktrace_records = 25;
//    void* buffer[max_stacktrace_records];
//    std::ostringstream ostream;

//    const size_t stacktrace_size = capture_stacktrace(buffer, max_stacktrace_records);
//    for (size_t i = 0; i < stacktrace_size; ++i) {
//        const void* address = buffer[i];
//        const char* symbol = "";
//        DL_info info;
//        if (dladdr(address, &info) && info.dli_sname) {
//            symbol = info.dli_sname;
//        }
//        ostream << "  " << std::setw(2) << ": " << address << " " << symbol << std::endl;
//    }
//    spdlog::critical("{}", ostream.str());
//}
//#endif// defined(__ANDROID__)

void runtime::stacktrace_dump()
{
    // clang-format off
#if defined(__ANDROID__)
    android_stacktrace_dump_implementation();
#elif defined(__FreeBSD__) || defined(__linux__) || defined(__APPLE__)
    unix_stacktrace_dump_implementation();
#endif

//#if defined(__unix__ ) || defined(__unix) || \
//   (defined(__APPLE__) && defined(__MACH__))
//    unix_stacktrace_dump_implementation();
//#elif defined(__ANDROID__)
//    android_stacktrace_dump_implementation();
//#endif// defined __unix__ || defined __APPLE__
    // clang-format on
}
