#include <gtest/gtest.h>
#include "20.hpp"

TEST(Day20, day20){
  std::vector<std::string> input = Common::read_file("test_input_20");
  const auto [result1, result2] = Day20::day20(input);
  
  EXPECT_EQ(result1, 0);
  EXPECT_EQ(result2, 0);
}
