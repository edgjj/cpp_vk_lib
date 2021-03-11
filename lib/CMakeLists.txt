include_directories(../dependencies)
include_directories(include/cpp_vk_lib)

#add_definitions(-DVK_CURL_DEBUG)
add_definitions(-DAPI_V="5.130")

set(COMMON_CXX_FLAGS "-Werror -Wall -Wextra -Wcast-qual -Weffc++ -Wsign-promo -Wno-unused -Wcast-align -Woverloaded-virtual -Wno-parentheses")

if (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64")
    set(CMAKE_CXX_FLAGS "${COMMON_CXX_FLAGS} -O2 -msse3 -march=native -mtune=generic")
elseif(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "i686")
    set(CMAKE_CXX_FLAGS "${COMMON_CXX_FLAGS} -O2 -msse3 -m32 -march=i686 -mtune=generic")
else()
    set(CMAKE_CXX_FLAGS "${COMMON_CXX_FLAGS} -O2 -march=native")
endif()

add_library(lib-simdjson INTERFACE)
target_compile_features(lib-simdjson INTERFACE cxx_std_17)
target_include_directories(lib-simdjson INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCDIR}>)
install(TARGETS lib-simdjson EXPORT simdjson-config INCLUDES DESTINATION dependencies)

file(GLOB_RECURSE SRC "*.hpp" "*.cpp")
set(LOGGER_SRC ../dependencies/logger/logger.cpp)
add_library(cpp_vk_lib SHARED ${SRC} ${LOGGER_SRC})
target_link_libraries(cpp_vk_lib simdjson)
