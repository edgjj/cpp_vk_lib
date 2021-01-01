TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

LIBS        += ../lib_vk.so -lcurlpp -lsimdjson
INCLUDEPATH += ../

HEADERS += \
        download_voice_message.hpp          \
        forward_community_post.hpp          \
        long_poll_api.hpp                   \
        search_documents.hpp                \
        upload_audio_message.hpp            \
        upload_audio_to_user_playlist.hpp   \
        upload_chat_photo.hpp               \
        upload_photo.hpp                    \

SOURCES += \
        main.cpp                            \
