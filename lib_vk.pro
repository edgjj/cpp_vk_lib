TEMPLATE = app
CONFIG  += console c++17
CONFIG  -= app_bundle
CONFIG  -= qt
LIBS    += -lcurlpp -lcurl -lsimdjson
QMAKE_CXXFLAGS += \
        -Wall -Wextra -pedantic -Wcast-align                              \
        -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization           \
        -Winit-self -Wold-style-cast -Wundef -Wno-unused                  \
        -Wformat=2 -Winit-self -Wmissing-include-dirs                     \
        -Wold-style-cast -Woverloaded-virtual -Wredundant-decls           \
        -Wshadow -Wsign-promo -Wstrict-overflow=5 -Wundef -Wno-unused     \
        -Wno-variadic-macros -Wno-parentheses -fdiagnostics-show-option   \

SOURCES += \
        main.cpp                                    \
        lib/src/api/long_poll_api.cpp               \
        lib/src/api/base_object.cpp                 \
        lib/src/attachment/attachment.cpp           \
        lib/src/document/common_document.cpp        \
        lib/src/events/common_event.cpp             \
        lib/src/lib/network.cpp                     \
        lib/src/methods/audio.cpp                   \
        lib/src/methods/docs.cpp                    \
        lib/src/methods/photos.cpp                  \
        lib/src/methods/video.cpp                   \
        lib/src/methods/messages.cpp                \
        lib/src/events/message_new.cpp              \
        lib/src/events/wall_post_new.cpp            \

HEADERS += \
        lib/include/api/base_object.hpp             \
        lib/include/api/long_poll_api.hpp           \
        lib/include/attachment/attachment.hpp       \
        lib/include/document/common_document.hpp    \
        lib/include/events/common_event.hpp         \
        lib/include/lib/common_error.hpp            \
        lib/include/lib/network.hpp                 \
        lib/include/methods/audio.hpp               \
        lib/include/methods/docs.hpp                \
        lib/include/methods/photos.hpp              \
        lib/include/methods/video.hpp               \
        lib/include/methods/messages.hpp            \
        lib/include/events/message_new.hpp          \
        lib/include/events/wall_post_new.hpp
