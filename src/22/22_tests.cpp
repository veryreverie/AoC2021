#include <gtest/gtest.h>
#include "22.hpp"

TEST(Day22, day22){
  std::vector<std::string> input = Common::read_file("test_input_22");
  const auto [result1, result2] = Day22::day22(input);
  
  EXPECT_EQ(result1, 0);
  EXPECT_EQ(result2, 0);
}
