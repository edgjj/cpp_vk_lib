include_directories(../lib/include)
include_directories(../lib/include/cpp_vk_lib)
include_directories(../dependencies/spdlog/include)

set(COMMON_CXX_FLAGS "-fPIC -pedantic -fstack-protector -Wall -Wextra -Wcast-qual -Weffc++ -Wsign-promo -Wno-unused -Wcast-align -Woverloaded-virtual -Wno-parentheses")

set(CMAKE_CXX_FLAGS "${COMMON_CXX_FLAGS} -O2 -msse3 -march=native -mtune=generic")

file(GLOB_RECURSE SRC "*.hpp" "*.cpp")
add_executable(bot ${SRC})

find_library(cpp_vk_lib HINTS "../lib")

target_link_libraries(bot cpp_vk_lib curlpp)
