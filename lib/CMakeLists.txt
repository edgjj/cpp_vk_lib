include_directories(include)
include_directories(../dependencies)

#add_definitions(-DVK_CURL_DEBUG)
add_definitions(-DAPI_V="5.130")

set(COMMON_CXX_FLAGS "-Werror -Wall -Wextra -Wcast-qual -Wsign-promo -Wno-unused -Wcast-align -Woverloaded-virtual -Wno-parentheses"
)

if (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64")
    set(CMAKE_CXX_FLAGS "${COMMON_CXX_FLAGS} -O2 -msse3 -march=native -mtune=generic")
elseif(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "i686")
    set(CMAKE_CXX_FLAGS "${COMMON_CXX_FLAGS} -O2 -msse3 -m32 -march=i686 -mtune=generic")
else()
    set(CMAKE_CXX_FLAGS "${COMMON_CXX_FLAGS} -O2 -march=native")
endif()

set(ATTACHMENT_SRC include/attachment/attachment.hpp)
set(COMMON_SRC include/cpp_vk_lib/common.hpp)

set(CONFIG_SRC
  include/config/loader.hpp
  src/config/loader.cpp
)
set(DOCUMENT_SRC
  include/document/common.hpp
  src/document/common.cpp
)
set(EVENTS_SRC
  include/events/common_event.hpp
  include/events/message_new.hpp
  include/events/wall_post_new.hpp
  include/events/wall_reply_new.hpp
  include/events/wall_repost.hpp
  include/events/handlers/attachment_handler.hpp
  include/events/handlers/message_action_handler.hpp
  src/events/common_event.cpp
  src/events/message_new.cpp
  src/events/wall_post_new.cpp
  src/events/wall_reply_new.cpp
  src/events/handlers/attachment_handler.cpp
)
set(EXCEPTION_SRC
  include/exception/error_processor.hpp
  include/exception/exception.hpp
  src/exception/error_processor.cpp
)
set(KEYBOARD_SRC
  include/keyboard/colors.hpp
  include/keyboard/flags.hpp
  include/keyboard/layout.hpp
  include/keyboard/buttons/location.hpp
  include/keyboard/buttons/open_app.hpp
  include/keyboard/buttons/text.hpp
  include/keyboard/buttons/vk_pay.hpp
  src/keyboard/layout.cpp
)
set(METHOD_UTILS_SRC
  include/method_utils/method_utils.hpp
  include/method_utils/message_constructor.hpp
  src/method_utils/method_utils.cpp
)
set(LONG_POLL_SRC
  include/long_poll/api.hpp
  include/long_poll/data.hpp
  src/long_poll/api.cpp
)
set(METHOD_SRC
  include/methods/audio.hpp
  include/methods/docs.hpp
  include/methods/groups.hpp
  include/methods/messages.hpp
  include/methods/photos.hpp
  include/methods/utils.hpp
  include/methods/video.hpp
  src/methods/audio.cpp
  src/methods/docs.cpp
  src/methods/groups.cpp
  src/methods/photos.cpp
  src/methods/video.cpp
  src/methods/messages.cpp
  src/methods/utils.cpp
)
set(MISC_SRC
  include/misc/cppdefs.hpp
  include/net/client.hpp
  src/net/client.cpp
)
set(OAUTH_SRC
  include/oauth/client.hpp
  src/oauth/client.cpp
)
set(PROCESSING_SRC
  include/processing/at_program_exit.hpp
  include/processing/backtrace.hpp
  include/processing/task_queue.hpp
  src/processing/task_queue.cpp
)
set(STRING_UTILS_SRC
  include/string_utils/implementation/format.hpp
  include/string_utils/implementation/join.hpp
  include/string_utils/implementation/lazy_split.hpp
  include/string_utils/implementation/split.hpp
  include/string_utils/string_utils.hpp
  include/string_utils/unicode/ostream.hpp
)
set(LOGGER_SRC
  ../dependencies/logger/logger.cpp
)

add_library(cpp_vk_lib SHARED main.cpp ${ATTACHMENT_SRC} ${COMMON_SRC} ${CONFIG_SRC} ${DOCUMENT_SRC} ${EVENTS_SRC}
  ${EXCEPTION_SRC} ${KEYBOARD_SRC} ${METHOD_UTILS_SRC} ${LONG_POLL_SRC} ${METHOD_SRC} ${MISC_SRC}
  ${OAUTH_SRC} ${PROCESSING_SRC} ${STRING_UTILS_SRC} ${LOGGER_SRC})
target_link_libraries(cpp_vk_lib simdjson)
