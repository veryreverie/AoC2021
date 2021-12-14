#include <gtest/gtest.h>
#include "10.hpp"

TEST(Day10, day10){
  std::vector<std::string> input = read_file("test_input_10");
  const auto [result1, result2] = day10(input);
  
  EXPECT_EQ(result1, 26397);
  EXPECT_EQ(result2, 288957);
}
