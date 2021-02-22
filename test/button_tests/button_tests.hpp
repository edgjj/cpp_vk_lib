#ifndef VK_BUTTON_TESTS_H
#define VK_BUTTON_TESTS_H

#include <gtest/gtest.h>
#include "keyboard/layout.hpp"

namespace keyboard = vk::keyboard;

TEST(keyboard, location_button) {
  keyboard::layout l;
  l.add_row({
    keyboard::location_button()
  });

  ASSERT_EQ(l.serialize(),
    R"({"buttons":[[{"action":{"type":"location","payload":"{\"button\":\"1\"}"}}]]})");
}

TEST(keyboard, open_app_layout) {
  keyboard::layout l(keyboard::flag::one_time);
  l.add_row({
    keyboard::open_app_button(100, 200, "hash", "label")
  });

  ASSERT_EQ(l.serialize(),
    R"({"one_time":true,"buttons":[[{"action":{"type":"open_app","app_id":100,"owner_id":200,"hash":"hash","label":"label"}}]]})");
}

TEST(keyboard, text_layout) {
  keyboard::layout l(keyboard::flag::one_time);
  l.add_row({
    keyboard::text_button(keyboard::color::blue, "1"),
    keyboard::text_button(keyboard::color::blue, "2")
  });

  ASSERT_EQ(l.serialize(),
    R"({"one_time":true,"buttons":[[{"action":{"type":"text","payload":"{\"button\":\"1\"}","label":"1"},"color":"primary"},{"action":{"type":"text","payload":"{\"button\":\"1\"}","label":"2"},"color":"primary"}]]})");
}

TEST(keyboard, vk_pay_button) {
  keyboard::layout l(keyboard::flag::one_time);
  l.add_row({
    keyboard::vk_pay_button("hash")
  });

  ASSERT_EQ(
    l.serialize(),
    R"({"one_time":true,"buttons":[[{"action":{"type":"vkpay","hash":"hash"}}]]})"
  );
}

#endif // VK_BUTTON_TESTS_H
