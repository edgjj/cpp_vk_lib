include_directories(../dependencies)
include_directories(../dependencies/spdlog/include)
include_directories(include/cpp_vk_lib)

#add_definitions(-DVK_CURL_DEBUG)
add_definitions(-DAPI_V="5.130")

set(extra_warnings TRUE)
set(find_leaks TRUE)

set(common_flags "-fPIC -Wall -Wextra -Werror -Weffc++ -pedantic -Wshadow -Wunused-parameter")

if (${find_leaks})
  set(find_leaks_flags "-fsanitize=leak -fstack-protector")
else()
  set(find_leaks_flags "")
endif()

if (${extra_warnings})
  set(extra_warnings_flags "-Wcast-qual -Wnon-virtual-dtor -Wreturn-type -Wsign-promo -Wno-unused -Wcast-align -Woverloaded-virtual -Wno-parentheses")
else()
  set(extra_warnings_flags "")
endif()

if (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64")
  set(CMAKE_CXX_FLAGS "${common_flags} ${extra_warnings_flags} ${find_leaks_flags} -O2 -msse3 -march=x86-64 -mtune=generic")
elseif(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "i686")
  set(CMAKE_CXX_FLAGS "${common_flags} ${extra_warnings_flags} ${find_leaks_flags} -O2 -msse3 -m32 -march=i686 -mtune=generic")
else()
  set(CMAKE_CXX_FLAGS "${common_flags} ${extra_warnings_flags} ${find_leaks_flags} -O2 -march=native")
endif()

add_library(lib-simdjson INTERFACE)
target_compile_features(lib-simdjson INTERFACE cxx_std_17)
target_include_directories(lib-simdjson INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCDIR}>)
install(TARGETS lib-simdjson EXPORT simdjson-config INCLUDES DESTINATION dependencies)

file(GLOB_RECURSE SRC "*.hpp" "*.cpp")
add_library(cpp_vk_lib SHARED ${SRC})
target_link_libraries(cpp_vk_lib simdjson)
