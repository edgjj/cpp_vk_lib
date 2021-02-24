include_directories(include)
include_directories(../dependencies)
include_directories(../dependencies/curl/include/curl)

add_definitions(-DVK_CURL_DEBUG)
add_definitions(-DAPI_V="5.130")

message(${CMAKE_CURRENT_BINARY_DIR})
if (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64")
    set(CMAKE_CXX_FLAGS "-O2 -msse3 -march=native -mtune=generic")
elseif(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "i686")
    set(CMAKE_CXX_FLAGS "-O2 -msse3 -m32 -march=i686 -mtune=generic")
else()
    set(CMAKE_CXX_FLAGS "-O2 -march=native")
endif()

set(HEADERS
  include/method_utils/method_utils.hpp

  include/attachment/attachment.hpp

  include/config/loader.hpp

  include/cpp_vk_lib/common.hpp

  include/document/common_document.hpp

  include/events/common_event.hpp
  include/events/message_new.hpp
  include/events/wall_post_new.hpp
  include/events/wall_reply_new.hpp
  include/events/wall_repost.hpp
  include/events/handlers/attachment_handler.hpp
  include/events/handlers/message_action_handler.hpp

  include/keyboard/colors.hpp
  include/keyboard/flags.hpp
  include/keyboard/layout.hpp
  include/keyboard/location_button.hpp
  include/keyboard/open_app_button.hpp
  include/keyboard/text_button.hpp
  include/keyboard/vk_pay_button.hpp

  include/long_poll/long_poll_api.hpp
  include/long_poll/long_poll_data.hpp

  include/methods/audio.hpp
  include/methods/docs.hpp
  include/methods/groups.hpp
  include/methods/messages.hpp
  include/methods/photos.hpp
  include/methods/utils.hpp
  include/methods/video.hpp

  include/misc/cppdefs.hpp

  include/net/network_client.hpp

  include/oauth/client.hpp

  include/processing/backtrace.hpp
  include/processing/error_handler.hpp
  include/processing/exception.hpp
  include/processing/task_queue.hpp

  include/string_utils/implementation/format.hpp
  include/string_utils/implementation/join.hpp
  include/string_utils/implementation/lazy_split.hpp
  include/string_utils/implementation/split.hpp
  include/string_utils/string_utils.hpp
  include/string_utils/unicode/ostream.hpp
)

set(SOURCES
  src/method_utils/method_utils.cpp

  src/config/loader.cpp

  src/document/common_document.cpp

  src/events/common_event.cpp
  src/events/message_new.cpp
  src/events/wall_post_new.cpp
  src/events/wall_reply_new.cpp
  src/events/handlers/attachment_handler.cpp

  src/keyboard/layout.cpp

  src/long_poll/long_poll_api.cpp

  src/methods/audio.cpp
  src/methods/docs.cpp
  src/methods/groups.cpp
  src/methods/photos.cpp
  src/methods/video.cpp
  src/methods/messages.cpp
  src/methods/utils.cpp

  src/net/network_client.cpp

  src/oauth/client.cpp

  src/processing/task_queue.cpp
)

add_library(
    cpp_vk_lib
    SHARED
    ${HEADERS}
    ${SOURCES}
    main.cpp
    ../dependencies/logger/logger.cpp
)
target_link_libraries(
    cpp_vk_lib simdjson
)
