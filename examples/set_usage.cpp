
#include <map>
#include <string>

#include <gtest/gtest.h>

TEST(set_usage, Set) {
  std::set<std::string> ex1 = {"hello", "world", "goodbye", "foo", "blah"};
  ASSERT_EQ(ex1.size(), 5);
  ASSERT_EQ(ex1.count("hello"), 1);

  const std::set ex1_const = ex1;
  for (const auto &key : ex1_const) {
    ASSERT_GT(ex1.count(key), 0);
  }
  auto itr = ex1.find("hello");
  const std::string &key = *itr;
  ASSERT_EQ(key, "hello");
  ex1.erase(itr);
  ASSERT_EQ(ex1.size(), 4);
}
