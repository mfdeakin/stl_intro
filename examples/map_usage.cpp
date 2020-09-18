
#include <map>
#include <string>

#include <gtest/gtest.h>

TEST(map_usage, Map) {
  std::map<std::string, std::string> ex = {{"hello", "goodbye"},
                                           {"foo", "blah"}};
  ASSERT_EQ(ex.size(), 2);
  ex["hello"] = "world";
  ASSERT_EQ(ex.size(), 2);

  ASSERT_ANY_THROW(ex.at("World"));

  const std::map ex_const = ex;
  for (const auto &[key, value] : ex_const) {
    ASSERT_GT(ex.count(key), 0);
    // Error - operator[] is not constant
    ASSERT_EQ(ex[key], value);
    // ASSERT_EQ(ex.at(key), value);
  }
  auto itr = ex.find("hello");
  const auto &[k, v] = *itr;
  const std::string &key = itr->first;
  ASSERT_EQ(k, key);
  ASSERT_EQ(k, "hello");
  const std::string &value = itr->second;
  ASSERT_EQ(v, value);
  ASSERT_EQ(v, "world");
  ex.erase(itr);
  ASSERT_EQ(ex.size(), 1);
}
