#include <gtest/gtest.h>
#include "15.hpp"

TEST(Day15, day15){
  std::vector<std::string> input = Common::read_file("test_input_15");
  const auto [result1, result2] = Day15::day15(input);
  
  EXPECT_EQ(result1, 40);
  EXPECT_EQ(result2, 315);
}
