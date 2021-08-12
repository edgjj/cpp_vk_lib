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

#if (NOT DEFINED CPP_VK_LIB_LOG_LEVEL)
#  add_definitions(-DCPP_VK_LIB_LOG_LEVEL="trace")
#else()
#  add_definitions(-DCPP_VK_LIB_LOG_LEVEL="${CPP_VK_LIB_LOG_LEVEL}")
#endif()

add_subdirectory(modules)
add_subdirectory(cpp_vk_lib)

if (CPP_VK_LIB_BUILD_TESTS)
  include(cmake/build_tests.cmake)
endif()

if (CPP_VK_LIB_BUILD_EXAMPLE)
  include(cmake/build_example.cmake)
endif()
