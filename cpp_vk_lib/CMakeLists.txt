set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall -Wextra -Werror -Wunused -Wwrite-strings -Wimplicit-fallthrough -pedantic -O3")

if (CMAKE_SYSTEM_NAME STREQUAL "FreeBSD")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated -Wno-deprecated-declarations")
    include_directories(/usr/local/include)
    link_directories(/usr/local/lib)
endif()

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS YES CACHE BOOL "Export all symbols")

set(SRC
    ../cpp_vk_lib/src/vk/implementation.cpp
    ../cpp_vk_lib/src/runtime/implementation.cpp)

if (CPP_VK_LIB_STATIC_BUILD)
    add_library(cpp_vk_lib STATIC ${SRC})
else()
    add_library(cpp_vk_lib SHARED ${SRC})
endif()

target_link_libraries(cpp_vk_lib PRIVATE curl)
target_link_libraries(cpp_vk_lib PRIVATE simdjson)
#[[Must be linked as PUBLIC to be able change logging level from user code]]
target_link_libraries(cpp_vk_lib PUBLIC spdlog)

target_include_directories(cpp_vk_lib PRIVATE include)
target_include_directories(cpp_vk_lib PRIVATE ../modules/spdlog/include)
target_include_directories(cpp_vk_lib PRIVATE ../modules/asio/asio/include)
