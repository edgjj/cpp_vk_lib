#pragma once

#ifndef VK_COMMON_H
#define VK_COMMON_H

#include "api/service.hpp"
#include "api/long_poll_api.hpp"

#include "attachment/attachment.hpp"

#include "document/common_document.hpp"

#include "events/handlers/attachment_handler.hpp"
#include "events/handlers/message_action_handler.hpp"
#include "events/common_event.hpp"
#include "events/message_new.hpp"
#include "events/wall_post_new.hpp"
#include "events/wall_reply_new.hpp"

#include "methods/audio.hpp"
#include "methods/docs.hpp"
#include "methods/groups.hpp"
#include "methods/messages.hpp"
#include "methods/photos.hpp"
#include "methods/utils.hpp"
#include "methods/video.hpp"

#include "misc/backtrace.hpp"
#include "misc/cppdefs.hpp"

#include "oauth/client.hpp"

#include "processing/thread_pool.hpp"
#include "processing/exception.hpp"

#include "string_util/string_util.hpp"

#endif // VK_COMMON_H
