#include <gtest/gtest.h>
#include "19.hpp"

TEST(Day19, day19){
  std::vector<std::string> input = Common::read_file("test_input_19");
  const auto [result1, result2] = Day19::day19(input);
  
  EXPECT_EQ(result1, 0);
  EXPECT_EQ(result2, 0);
}
