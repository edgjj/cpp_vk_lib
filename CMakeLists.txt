cmake_minimum_required(VERSION 3.19)

project(
    cpp_vk_lib
    DESCRIPTION "C++ vk library"
    LANGUAGES CXX
)

string(
    COMPARE EQUAL
    "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}"
    IS_TOP_PROJECT
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MACOSX_RPATH OFF)
set(CMAKE_THREAD_PREFER_PTHREAD ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)
set(CMAKE_VERBOSE_MAKEFILE OFF)

set(BUILD_SHARED_LIBS ON CACHE BOOL "Link simdjson as shared library")

add_subdirectory(modules)
add_subdirectory(cpp_vk_lib)

if (IS_TOP_PROJECT)
    enable_testing()
    add_subdirectory(tests)
    add_subdirectory(examples)
endif()
