cmake_minimum_required(VERSION 3.19)

project(cpp_vk_lib DESCRIPTION "C++ vk library" LANGUAGES CXX)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../build)
set(EXECUTABLE_OUTPUT_PATH ../build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../build)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_MACOSX_RPATH OFF)
set(CMAKE_THREAD_PREFER_PTHREAD ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)
set(CMAKE_VERBOSE_MAKEFILE OFF)

set(BUILD_SHARED_LIBS ON CACHE BOOL "Link simdjson as shared library")
option(CPP_VK_LIB_STATIC_BUILD "Link cpp_vk_lib as static library" OFF)

message("-- CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")

add_subdirectory(modules)
add_subdirectory(cpp_vk_lib)

include(cmake/testing.cmake)

include_directories(modules/asio/asio/include)
add_executable(long_poll_example test/long_poll/long_poll.cpp)
target_link_libraries(long_poll_example cpp_vk_lib)
