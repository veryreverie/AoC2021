#include <gtest/gtest.h>
#include "18.hpp"

TEST(Day18, day18){
  std::vector<std::string> input = read_file("test_input_18");
  const auto [result1, result2] = day18(input);
  
  EXPECT_EQ(result1, 0);
  EXPECT_EQ(result2, 0);
}
