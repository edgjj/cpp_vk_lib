#include "string_util_tests/join_tests.hpp"
#include "string_util_tests/format_tests.hpp"
#include "string_util_tests/split_tests.hpp"
#include "string_util_tests/convert_tests.hpp"

#include "attachment_tests/attachment_tests.hpp"

#include "button_tests/button_tests.hpp"

#include "event_tests/message_new_tests.hpp"
#include "event_tests/wall_post_new_tests.hpp"
#include "event_tests/wall_reply_new_tests.hpp"


int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
