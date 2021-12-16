#include <gtest/gtest.h>
#include "08.hpp"

TEST(Day08, day08){
  std::vector<std::string> input = Common::read_file("test_input_08");
  const auto [result1, result2] = Day08::day08(input);
  
  EXPECT_EQ(result1, 26);
  EXPECT_EQ(result2, 61229);
}
