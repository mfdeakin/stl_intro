
#include <map>
#include <string>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("map usage", "map") {
  std::map<std::string, std::string> ex = {{"hello", "goodbye"},
                                           {"foo", "blah"}};
  REQUIRE(ex.size() == 2);
  ex["hello"] = "world";
  REQUIRE(ex.size() == 2);

  REQUIRE_THROWS(ex.at("World"));

  const std::map ex_const = ex;
  for (const auto &[key, value] : ex_const) {
    REQUIRE(ex.count(key) > 0);
    // Error - operator[] is not constant
    REQUIRE(ex[key] == value);
    // REQUIRE(ex.at(key) == value);
  }
  auto itr = ex.find("hello");
  const auto &[k, v] = *itr;
  const std::string &key = itr->first;
  REQUIRE(k == key);
  REQUIRE(k == "hello");
  const std::string &value = itr->second;
  REQUIRE(v == value);
  REQUIRE(v == "world");
  ex.erase(itr);
  REQUIRE(ex.size() == 1);
}
