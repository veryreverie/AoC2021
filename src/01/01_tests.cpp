#include <gtest/gtest.h>
#include "01.hpp"

TEST(Day01, day01){
  std::vector<std::string> input = read_file("test_input_01");
  const auto [result1, result2] = day01(input);
  
  EXPECT_EQ(result1, 7);
  EXPECT_EQ(result2, 5);
}
