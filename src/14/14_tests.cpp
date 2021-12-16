#include <gtest/gtest.h>
#include "14.hpp"

TEST(Day14, day14){
  std::vector<std::string> input = Common::read_file("test_input_14");
  const auto [result1, result2] = Day14::day14(input);
  
  EXPECT_EQ(result1, 1588);
  EXPECT_EQ(result2, 2188189693529);
}
