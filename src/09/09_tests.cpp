#include <gtest/gtest.h>
#include "09.hpp"

TEST(Day09, day09){
  std::vector<std::string> input = read_file("test_input_09");
  const auto [result1, result2] = day09(input);
  
  EXPECT_EQ(result1, 15);
  EXPECT_EQ(result2, 1134);
}
