#include <gtest/gtest.h>
#include "21.hpp"

TEST(Day21, day21){
  std::vector<std::string> input = Common::read_file("test_input_21");
  const auto [result1, result2] = Day21::day21(input);
  
  EXPECT_EQ(result1, 0);
  EXPECT_EQ(result2, 0);
}
