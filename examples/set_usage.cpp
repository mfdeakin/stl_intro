
#include <set>
#include <string>
#include <unordered_set>

#include <gtest/gtest.h>

class comp_set_obj {
public:
  comp_set_obj(const std::string &s_, const int i_) : s(s_), i(i_) {}

  bool operator==(const comp_set_obj &rhs) const { return s == rhs.s; }
  bool operator<=(const comp_set_obj &rhs) const { return s <= rhs.s; }
  bool operator>=(const comp_set_obj &rhs) const { return rhs <= *this; }
  bool operator<(const comp_set_obj &rhs) const { return s < rhs.s; }
  bool operator>(const comp_set_obj &rhs) const { return rhs < *this; }

private:
  std::string s;
  int i;
};

TEST(set_usage, Set) {
  std::set<std::string> ex1 = {"hello", "world", "goodbye", "foo", "blah"};
  ASSERT_EQ(ex1.size(), 5);
  ASSERT_EQ(ex1.count("hello"), 1);

  const std::set ex1_const = ex1;
  for (auto itr = ex1_const.begin(); itr != ex1_const.end(); ++itr) {
    const std::string &key = *itr;
    ASSERT_EQ(ex1.count(key), 1);
  }
  for (const auto &key : ex1_const) {
    ASSERT_EQ(ex1.count(key), 1);
  }

  auto itr = ex1.find("hello");
  const std::string &key = *itr;
  ASSERT_EQ(key, "hello");
  ex1.erase(itr);
  ASSERT_EQ(ex1.size(), 4);
}

class incomp_set_obj {
public:
  incomp_set_obj(const std::string &s_, const int i_) : s(s_), i(i_) {}

  bool operator==(const incomp_set_obj &rhs) const { return s == rhs.s; }

  struct hash {
    size_t operator()(const incomp_set_obj &c) const {
      return std::hash<std::string>()(c.s);
    }
  };

private:
  std::string s;
  int i;
};

TEST(unordered_set_usage, Set) {
  std::unordered_set<incomp_set_obj, incomp_set_obj::hash> ex2;
  ASSERT_EQ(ex2.size(), 0);
  ex2.insert(incomp_set_obj("no", 5));
  ASSERT_EQ(ex2.size(), 1);
  ex2.insert(incomp_set_obj("no", 5));
  ASSERT_EQ(ex2.size(), 1);
  ex2.insert(incomp_set_obj("no", 12));
  ASSERT_EQ(ex2.size(), 1);
  ex2.insert(incomp_set_obj("yes", 5));
  ASSERT_EQ(ex2.size(), 2);
}
