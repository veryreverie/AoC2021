#include <gtest/gtest.h>
#include "05.hpp"

TEST(Day05, day05){
  std::vector<std::string> input = Common::read_file("test_input_05");
  const auto [result1, result2] = Day05::day05(input);
  
  EXPECT_EQ(result1, 5);
  EXPECT_EQ(result2, 12);
}
