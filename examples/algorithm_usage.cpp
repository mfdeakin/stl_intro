
#include <map>
#include <string>

#include <gtest/gtest.h>

TEST(sort, Algorithms) {
  std::vector<std::string> ex{"hello", "world", "goodbye", "foo", "blah"};
  ASSERT_EQ(ex.size(), 5);
  std::sort(ex.begin(), ex.end());
  ASSERT_EQ(ex[0], "blah");
  ASSERT_EQ(ex[1], "foo");
  ASSERT_EQ(ex[2], "goodbye");
  ASSERT_EQ(ex[3], "hello");
  ASSERT_EQ(ex[4], "world");
}

double doubleValue(const double v) { return v * 2.0; }
void doubleValueInPlace(double &v) { v *= 2.0; }

TEST(transform, Algorithms) {
  std::vector<double> force{0.6, 32.0, 543.0};
  std::vector<double> doubled_force(force.size());
  std::transform(force.begin(), force.end(), doubled_force.begin(),
                 doubleValue);
  ASSERT_EQ(doubled_force[0], force[0] * 2.0);
  ASSERT_EQ(doubled_force[1], force[1] * 2.0);
  ASSERT_EQ(doubled_force[2], force[2] * 2.0);
}

TEST(for_each, Algorithms) {
  std::vector<double> force{0.6, 32.0, 543.0};
  std::for_each(force.begin(), force.end(), doubleValueInPlace);
  ASSERT_EQ(force[0] / 2.0, 0.6);
  ASSERT_EQ(force[1] / 2.0, 32.0);
  ASSERT_EQ(force[2] / 2.0, 543.0);
}

TEST(set_ops, Algorithms) {
  std::vector<int> vec_1 = {1, 2, 4, 8};
  std::sort(vec_1.begin(), vec_1.end());
  std::vector<int> vec_2 = {1, 2, 3, 4, 5};
  std::sort(vec_2.begin(), vec_2.end());

  std::vector<int> intersection;
  std::set_intersection(vec_1.begin(), vec_1.end(), vec_2.begin(), vec_2.end(),
                        std::inserter(intersection, intersection.begin()));
  for (const int v : intersection) {
    ASSERT_NE(std::find(vec_1.begin(), vec_1.end(), v), vec_1.end());
    ASSERT_NE(std::find(vec_2.begin(), vec_2.end(), v), vec_2.end());
  }

  std::vector<int> v_union;
  std::set_union(vec_1.begin(), vec_1.end(), vec_2.begin(), vec_2.end(),
                 std::inserter(v_union, v_union.begin()));
  for (const int v : v_union) {
    ASSERT_TRUE(std::find(vec_1.begin(), vec_1.end(), v) != vec_1.end() ||
                std::find(vec_2.begin(), vec_2.end(), v) != vec_2.end());
  }

  std::vector<int> diff;
  std::set_difference(vec_1.begin(), vec_1.end(), vec_2.begin(), vec_2.end(),
                      std::inserter(diff, diff.begin()));
  for (const int v : diff) {
    ASSERT_NE(std::find(vec_1.begin(), vec_1.end(), v), vec_1.end());
    ASSERT_EQ(std::find(vec_2.begin(), vec_2.end(), v), vec_2.end());
  }

  std::vector<int> sym_diff;
  std::set_symmetric_difference(vec_1.begin(), vec_1.end(), vec_2.begin(),
                                vec_2.end(),
                                std::inserter(sym_diff, sym_diff.begin()));
  for (const int v : diff) {
    ASSERT_TRUE(std::find(vec_1.begin(), vec_1.end(), v) != vec_1.end() ||
                std::find(vec_2.begin(), vec_2.end(), v) != vec_2.end());
    ASSERT_FALSE(std::find(vec_1.begin(), vec_1.end(), v) != vec_1.end() &&
                 std::find(vec_2.begin(), vec_2.end(), v) != vec_2.end());
  }
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
