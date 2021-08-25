find_library(cpp_vk_lib HINTS "../cpp_vk_lib")
include_directories(../cpp_vk_lib/include)
include_directories(../modules/spdlog/include)
include_directories(../modules/asio/asio/include)

set(EXECUTABLE_OUTPUT_PATH ../build)

if (CMAKE_SYSTEM_NAME STREQUAL "FreeBSD")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated -Wno-deprecated-declarations")
endif()

add_executable(tests main.cpp)
target_link_libraries(tests simdjson gtest cpp_vk_lib)
