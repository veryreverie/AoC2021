#include <gtest/gtest.h>
#include "06.hpp"

TEST(Day06, day06){
  std::vector<std::string> input = Common::read_file("test_input_06");
  const auto [result1, result2] = Day06::day06(input);
  
  EXPECT_EQ(result1, 5934);
  EXPECT_EQ(result2, 26984457539);
}
