
#include <map>
#include <numeric>
#include <string>
#include <utility>

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

bool pair_comp_1(const std::pair<int, int> &lhs,
                 const std::pair<int, int> &rhs) {
  return lhs.first < rhs.first;
}

bool pair_comp_2(const std::pair<int, int> &lhs,
                 const std::pair<int, int> &rhs) {
  return lhs.second < rhs.second;
}

TEST(sort_pair, Algorithms) {
  std::vector<std::pair<int, int>> ex{{3, 3}, {3, 1}, {3, 1}, {3, 0}, {3, 2},
                                      {3, 9}, {3, 3}, {3, 5}, {3, 8}, {3, 4},
                                      {3, 5}, {3, 2}, {2, 7}, {6, 1}, {6, 6},
                                      {0, 7}, {0, 3}, {0, 7}, {0, 5}, {2, 3}};
  std::sort(ex.begin(), ex.end(), pair_comp_2);
  std::sort(ex.begin(), ex.end(), pair_comp_1);

  int prev_1 = ex[0].first;
  int prev_2 = ex[0].second;
  for (const auto &[v1, v2] : ex) {
    ASSERT_GE(v1, prev_1);
    // Fails!
    // EXPECT_TRUE(v2 >= prev_2 || v1 > prev_1);
    prev_1 = v1;
    prev_2 = v2;
  }
}

TEST(stable_sort_pair, Algorithms) {
  std::vector<std::pair<int, int>> ex{{3, 3}, {3, 1}, {3, 1}, {3, 0}, {3, 2},
                                      {3, 9}, {3, 3}, {3, 5}, {3, 8}, {3, 4},
                                      {3, 5}, {3, 2}, {2, 7}, {6, 1}, {6, 6},
                                      {0, 7}, {0, 3}, {0, 7}, {0, 5}, {2, 3}};
  std::sort(ex.begin(), ex.end(), pair_comp_2);
  std::stable_sort(ex.begin(), ex.end(), pair_comp_1);
  int prev_1 = ex[0].first;
  int prev_2 = ex[0].second;
  for (const auto &[v1, v2] : ex) {
    ASSERT_GE(v1, prev_1);
    ASSERT_TRUE(v2 >= prev_2 || v1 > prev_1);
    prev_1 = v1;
    prev_2 = v2;
  }
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

TEST(transform_reduce, Algorithms) {
  std::vector<std::string> vec{"5.0", "6.0", "-2.0"};
  double sum =
      std::transform_reduce(vec.begin(), vec.end(), 0.0, std::plus<>(),
                            [](const std::string &s) { return std::stod(s); });
  ASSERT_EQ(sum, 9.0);
}

TEST(for_each, Algorithms) {
  std::vector<double> force{0.6, 32.0, 543.0};
  std::for_each(force.begin(), force.end(), doubleValueInPlace);
  ASSERT_EQ(force[0] / 2.0, 0.6);
  ASSERT_EQ(force[1] / 2.0, 32.0);
  ASSERT_EQ(force[2] / 2.0, 543.0);
}

TEST(partial_sum, Algorithms) {
  std::vector<double> vec{5.0, 6.0, -2.0};
  std::vector<double> result(vec.size());
  std::partial_sum(vec.begin(), vec.end(), result.begin());
  ASSERT_EQ(result[0], 5.0);
  ASSERT_EQ(result[1], 11.0);
  ASSERT_EQ(result[2], 9.0);
}

TEST(inclusive_scan, Algorithms) {
  std::vector<double> vec{5.0, 6.0, -2.0};
  std::vector<double> result(vec.size());
  std::inclusive_scan(vec.begin(), vec.end(), result.begin());
  ASSERT_EQ(result[0], 5.0);
  ASSERT_EQ(result[1], 11.0);
  ASSERT_EQ(result[2], 9.0);
}

TEST(exclusive_scan, Algorithms) {
  std::vector<double> vec{5.0, 6.0, -2.0};
  std::vector<double> result(vec.size());
  std::exclusive_scan(vec.begin(), vec.end(), result.begin(), 0.0);
  ASSERT_EQ(result[0], 0.0);
  ASSERT_EQ(result[1], 5.0);
  ASSERT_EQ(result[2], 11.0);
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
