#include <gtest/gtest.h>
#include "09.hpp"

TEST(Day09, day09){
  std::vector<std::string> input = Common::read_file("test_input_09");
  const auto [result1, result2] = Day09::day09(input);
  
  EXPECT_EQ(result1, 15);
  EXPECT_EQ(result2, 1134);
}
