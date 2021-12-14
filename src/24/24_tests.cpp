#include <gtest/gtest.h>
#include "24.hpp"

TEST(Day24, day24){
  std::vector<std::string> input = read_file("test_input_24");
  const auto [result1, result2] = day24(input);
  
  EXPECT_EQ(result1, 0);
  EXPECT_EQ(result2, 0);
}
