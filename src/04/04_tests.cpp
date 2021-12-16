#include <gtest/gtest.h>
#include "04.hpp"

TEST(Day04, day04){
  std::vector<std::string> input = Common::read_file("test_input_04");
  const auto [result1, result2] = Day04::day04(input);
  
  EXPECT_EQ(result1, 4512);
  EXPECT_EQ(result2, 1924);
}
