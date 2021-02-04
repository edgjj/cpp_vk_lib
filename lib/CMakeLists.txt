include_directories(include)
include_directories(../dependencies)

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
    src/methods/photos.cpp
    src/methods/video.cpp
    src/methods/messages.cpp
    src/net/network_client.cpp
    src/processing/thread_pool.cpp
    ../dependencies/logger/logger.cpp
)
target_link_libraries(
    cpp_vk_lib
    avformat simdjson
)
