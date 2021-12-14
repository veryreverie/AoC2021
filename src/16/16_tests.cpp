#include <gtest/gtest.h>
#include "16.hpp"

TEST(Day16, day16){
  std::vector<std::string> input = read_file("test_input_16");
  const auto [result1, result2] = day16(input);
  
  EXPECT_EQ(result1, 0);
  EXPECT_EQ(result2, 0);
}
