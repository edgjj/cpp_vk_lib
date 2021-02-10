include_directories(include)
include_directories(../dependencies)

add_definitions(-DVK_CURL_DEBUG)

message(${CMAKE_CURRENT_BINARY_DIR})
if (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64")
    set(CMAKE_CXX_FLAGS "-O3 -msse3 -march=native -mtune=generic")
elseif(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "i686")
    set(CMAKE_CXX_FLAGS "-O3 -msse3 -m32 -march=i686 -mtune=generic")
else()
    set(CMAKE_CXX_FLAGS "-O3 -march=native")
endif()

add_library(
    cpp_vk_lib
    SHARED
    main.cpp
    src/api/long_poll_api.cpp
    src/api/base_object.cpp
    src/attachment/attachment.cpp
    src/document/common_document.cpp
    src/events/common_event.cpp
    src/events/message_new.cpp
    src/events/wall_post_new.cpp
    src/methods/audio.cpp
    src/methods/docs.cpp
    src/methods/groups.cpp
    src/methods/photos.cpp
    src/methods/video.cpp
    src/methods/messages.cpp
    src/methods/utils.cpp
    src/net/network_client.cpp
    src/oauth/client.cpp
    src/processing/thread_pool.cpp
    ../dependencies/logger/logger.cpp
)
target_link_libraries(
    cpp_vk_lib
    avformat simdjson
)
