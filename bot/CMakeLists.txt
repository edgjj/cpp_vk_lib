include_directories(../lib/include)
include_directories(../lib/include/cpp_vk_lib)
include_directories(../dependencies/spdlog/include)

if (NOT WIN32)
	set(COMMON_CXX_FLAGS "-fPIC -pedantic -fstack-protector -Wall -Wextra -Wcast-qual -Weffc++ -Wsign-promo -Wno-unused -Wcast-align -Woverloaded-virtual -Wno-parentheses")
else()
	set(COMMON_CXX_FLAGS "")
endif()

set(CMAKE_CXX_FLAGS "${COMMON_CXX_FLAGS} -O2 -march=native -mtune=generic")

file(GLOB_RECURSE SRC "*.hpp" "*.cpp")

if (WIN32)
	add_executable(bot ${SRC})	
else()
	add_executable(bot ${SRC} src/custom_methods/photos.hpp)
endif()

find_library(cpp_vk_lib HINTS "../lib")

if (WIN32)
	target_link_libraries(bot cpp_vk_lib unofficial::curlpp::curlpp)
else()
  target_link_libraries(bot cpp_vk_lib curlpp)
endif()
