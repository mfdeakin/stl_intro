
#include "vector.hpp"
#include <gtest/gtest.h>

TEST(construct, Vector) {
  std::vector<std::string> v;
  ASSERT_EQ(v.size(), 0);
  ASSERT_GE(v.capacity(), v.size());
}

TEST(push_back, Vector) {
  vector<std::string> v;
  const std::string test_str = "hello";
  constexpr size_t num_tests = 4097;
  for (size_t i = 0; i < num_tests; ++i) {
    v.push_back(test_str);
    ASSERT_EQ(v.size(), i + 1);
    ASSERT_GE(v.capacity(), v.size());
    ASSERT_EQ(v[i], test_str);
    ASSERT_EQ(v.at(i), test_str);
  }
  for (size_t i = 0; i < num_tests; ++i) {
    ASSERT_EQ(v.size(), num_tests);
    ASSERT_GE(v.capacity(), v.size());
    ASSERT_EQ(v[i], test_str);
    ASSERT_EQ(v.at(i), test_str);
  }
  const std::string new_str = "world";
  for (size_t i = 0; i < num_tests; ++i) {
    v[i] = new_str;
  }
}

TEST(iterate, Vector) {
  vector<std::string> v;
  constexpr size_t num_tests = 4097;
  for (size_t i = 0; i < num_tests; ++i) {
    v.push_back(std::to_string(i));
  }
  size_t i = 0;
  for (std::string &s : v) {
    ASSERT_EQ(i, std::stoul(s));
    i++;
  }
}

TEST(move_construct, Vector) {
  constexpr size_t num_tests = 4097;
  vector<size_t> v;
  for (size_t i = 0; i < num_tests; ++i) {
    v.push_back(i);
  }
  vector<size_t> v2 = std::move(v);
  ASSERT_EQ(v.size(), 0);
  ASSERT_EQ(v.capacity(), 0);
  ASSERT_EQ(v2.size(), num_tests);
  ASSERT_GE(v2.capacity(), num_tests);
}
