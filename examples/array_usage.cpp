
#include <array>
#include <gtest/gtest.h>

TEST(construct, Array) {
  std::array<std::string, 10> a;
  ASSERT_EQ(a.size(), 10);
}

TEST(iterate, Array) {
  constexpr size_t num_tests = 4097;
  std::array<std::string, num_tests> a;
  for (size_t i = 0; i < num_tests; ++i) {
    a[i] = std::to_string(i);
  }
  size_t i = 0;
  for (std::string &s : a) {
    ASSERT_EQ(i, std::stoul(s));
    i++;
  }
}

TEST(exception, Array) {
  std::array<std::string, 10> a;
  ASSERT_ANY_THROW(a.at(10));
}

constexpr size_t dim_1 = 20;
constexpr size_t dim_2 = 10;

void pass_array(std::array<std::string, dim_2> &a) {}
void pass_array(std::string *a) {}

void pass_2d_array(std::array<std::array<std::string, dim_2>, dim_1> &a) {}
void pass_2d_array(std::string a[][dim_2]) {}

TEST(pass, Array) {
  std::array<std::array<std::string, dim_2>, dim_1> a;
  pass_array(a[3]);
  pass_2d_array(a);
  std::string c_a[dim_1][dim_2];
  pass_array(c_a[3]);
  pass_2d_array(c_a);
}

class Base {
public:
  int member;
}; // sizeof base object is 4.

class Sub : public Base {
  double val;
}; // sizeof Sub object is 12.

TEST(access_subclass, Array) {
  Sub sub_array[5];
  sub_array[1].member = 123;
  Base *base_ptr = sub_array;
  base_ptr[1].member = 5;
  ASSERT_EQ(sub_array[1].member, 5);
}
