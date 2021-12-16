#include <gtest/gtest.h>
#include "13.hpp"

TEST(Day13, day13){
  std::vector<std::string> input = Common::read_file("test_input_13");
  const auto [result1, result2] = Day13::day13(input);
  
  EXPECT_EQ(result1, 17);
  EXPECT_EQ(result2, 0);
}
