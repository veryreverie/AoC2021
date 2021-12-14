#include <gtest/gtest.h>
#include "02.hpp"

TEST(Day02, day02){
  std::vector<std::string> input = read_file("test_input_02");
  const auto [result1, result2] = day02(input);
  
  EXPECT_EQ(result1, 150);
  EXPECT_EQ(result2, 900);
}
