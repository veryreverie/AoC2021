#include <gtest/gtest.h>
#include "25.hpp"

TEST(Day25, day25){
  std::vector<std::string> input = read_file("test_input_25");
  const auto [result1, result2] = day25(input);
  
  EXPECT_EQ(result1, 0);
  EXPECT_EQ(result2, 0);
}
