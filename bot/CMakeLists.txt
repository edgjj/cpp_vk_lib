include_directories(../lib/include)
include_directories(../lib/include/cpp_vk_lib)
include_directories(../dependencies/spdlog/include)

if (NOT WIN32)
  set(COMMON_CXX_FLAGS "-fPIC -pedantic -fstack-protector -Wall -Wextra -Wcast-qual -Wsign-promo -Wno-unused -Wcast-align -Woverloaded-virtual -Wno-parentheses")
else()
	set(COMMON_CXX_FLAGS "")
endif()

set(CMAKE_CXX_FLAGS "${COMMON_CXX_FLAGS} -O2")

file(GLOB_RECURSE SRC "*.hpp" "*.cpp")

add_executable(bot ${SRC})

find_library(cpp_vk_lib HINTS "../lib")

if (WIN32)
  target_link_libraries(bot cpp_vk_lib unofficial::curlpp::curlpp)
else()
  target_link_libraries(bot cpp_vk_lib curlpp)
endif()
