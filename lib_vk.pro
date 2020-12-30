TEMPLATE = app
CONFIG  += console c++17
CONFIG  -= app_bundle
CONFIG  -= qt
LIBS    += -lcurlpp -lcurl -lsimdjson

SOURCES += \
        main.cpp                                      \
        vkapi/src/api/long_poll_api.cpp               \
        vkapi/src/api/base_object.cpp                 \
        vkapi/src/attachment/attachment.cpp           \
        vkapi/src/document/common_document.cpp        \
        vkapi/src/events/common_event.cpp             \
        vkapi/src/lib/network.cpp                     \
        vkapi/src/methods/audio.cpp                   \
        vkapi/src/methods/docs.cpp                    \
        vkapi/src/methods/photos.cpp                  \
        vkapi/src/methods/video.cpp                   \
        vkapi/src/methods/messages.cpp                \
        vkapi/src/events/message_new.cpp              \
        vkapi/src/events/wall_post_new.cpp            \

HEADERS += \
        vkapi/include/api/base_object.hpp             \
        vkapi/include/api/long_poll_api.hpp           \
        vkapi/include/attachment/attachment.hpp       \
        vkapi/include/document/common_document.hpp    \
        vkapi/include/events/common_event.hpp         \
        vkapi/include/lib/common_error.hpp            \
        vkapi/include/lib/network.hpp                 \
        vkapi/include/methods/audio.hpp               \
        vkapi/include/methods/docs.hpp                \
        vkapi/include/methods/photos.hpp              \
        vkapi/include/methods/video.hpp               \
        vkapi/include/methods/messages.hpp            \
        vkapi/include/events/message_new.hpp          \
        vkapi/include/events/wall_post_new.hpp
