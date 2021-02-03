cmake_minimum_required(VERSION 3.5)

project(cpp_vk_lib, LANGUAGES CXX)
#add_definitions(-DVK_CURL_DEBUG)
message(CURRENT_DIR = ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS
    "-O2 -Wall -Wextra -ftree-vectorize -pedantic \
    -Wcast-align -Winit-self -Wold-style-cast \
    -Wstrict-overflow=5 -Wno-parentheses"
)

add_library(
    cpp_vk_lib
    SHARED
    main.cpp
    lib/src/api/long_poll_api.cpp
    lib/src/api/base_object.cpp
    lib/src/attachment/attachment.cpp
    lib/src/document/common_document.cpp
    lib/src/events/common_event.cpp
    lib/src/events/message_new.cpp
    lib/src/events/wall_post_new.cpp
    lib/src/methods/audio.cpp
    lib/src/methods/docs.cpp
    lib/src/methods/photos.cpp
    lib/src/methods/video.cpp
    lib/src/methods/messages.cpp
    lib/src/net/network_client.cpp
    lib/src/processing/thread_pool.cpp
    logger/logger.cpp
)
target_link_libraries(
    cpp_vk_lib
    avformat
)
