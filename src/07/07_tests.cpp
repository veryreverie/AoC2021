#include <gtest/gtest.h>
#include "07.hpp"

TEST(Day07, day07){
  std::vector<std::string> input = Common::read_file("test_input_07");
  const auto [result1, result2] = Day07::day07(input);
  
  EXPECT_EQ(result1, 37);
  EXPECT_EQ(result2, 168);
}
