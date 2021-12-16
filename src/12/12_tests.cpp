#include <gtest/gtest.h>
#include "12.hpp"

TEST(Day12, day12){
  std::vector<std::string> input = Common::read_file("test_input_12");
  const auto [result1, result2] = Day12::day12(input);
  
  EXPECT_EQ(result1, 226);
  EXPECT_EQ(result2, 3509);
}
