#include <gtest/gtest.h>
#include "15.hpp"

TEST(Day15, day15){
  std::vector<std::string> input = read_file("test_input_15");
  const auto [result1, result2] = day15(input);
  
  EXPECT_EQ(result1, 0);
  EXPECT_EQ(result2, 0);
}
