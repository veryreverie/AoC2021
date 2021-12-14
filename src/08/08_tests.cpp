#include <gtest/gtest.h>
#include "08.hpp"

TEST(Day08, day08){
  std::vector<std::string> input = read_file("test_input_08");
  const auto [result1, result2] = day08(input);
  
  EXPECT_EQ(result1, 26);
  EXPECT_EQ(result2, 61229);
}
