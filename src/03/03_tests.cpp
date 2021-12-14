#include <gtest/gtest.h>
#include "03.hpp"

TEST(Day03, day03){
  std::vector<std::string> input = read_file("test_input_03");
  const auto [result1, result2] = day03(input);
  
  EXPECT_EQ(result1, 198);
  EXPECT_EQ(result2, 230);
}
