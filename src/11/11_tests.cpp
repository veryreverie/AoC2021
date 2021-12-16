#include <gtest/gtest.h>
#include "11.hpp"

TEST(Day11, day11){
  std::vector<std::string> input = Common::read_file("test_input_11");
  const auto [result1, result2] = Day11::day11(input);
  
  EXPECT_EQ(result1, 1656);
  EXPECT_EQ(result2, 195);
}
