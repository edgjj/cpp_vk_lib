include_directories(../lib/include)
include_directories(../lib/include/cpp_vk_lib)

set(COMMON_CXX_FLAGS "-fPIC -pedantic -fsanitize=leak -fstack-protector -Wall -Wextra -Wcast-qual -Weffc++ -Wsign-promo -Wno-unused -Wcast-align -Woverloaded-virtual -Wno-parentheses")

if (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64")
  set(CMAKE_CXX_FLAGS "${COMMON_CXX_FLAGS} -O2 -msse3 -march=x86-64 -mtune=generic")
elseif(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "i686")
  set(CMAKE_CXX_FLAGS "${COMMON_CXX_FLAGS} -O2 -msse3 -m32 -march=i686 -mtune=generic")
else()
  set(CMAKE_CXX_FLAGS "${COMMON_CXX_FLAGS} -O2 -march=native")
endif()

file(GLOB_RECURSE SRC "*.hpp" "*.cpp")
add_executable(bot ${SRC})

target_link_libraries(bot -Lbuild cpp_vk_lib pthread curl curlpp -L../dependencies/simdjson simdjson)
