#include <gtest/gtest.h>
#include "23.hpp"

TEST(Day23, day23){
  std::vector<std::string> input = read_file("test_input_23");
  const auto [result1, result2] = day23(input);
  
  EXPECT_EQ(result1, 0);
  EXPECT_EQ(result2, 0);
}
