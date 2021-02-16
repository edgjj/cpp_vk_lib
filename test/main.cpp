#include "string_util_tests/join_tests.hpp"
#include "string_util_tests/format_tests.hpp"
#include "string_util_tests/split_tests.hpp"

#include "attachment_tests/attachment_tests.hpp"

#include "button_tests/button_tests.hpp"


int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
