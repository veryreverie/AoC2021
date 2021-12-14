#include <gtest/gtest.h>
#include "17.hpp"

TEST(Day17, day17){
  std::vector<std::string> input = read_file("test_input_17");
  const auto [result1, result2] = day17(input);
  
  EXPECT_EQ(result1, 0);
  EXPECT_EQ(result2, 0);
}
