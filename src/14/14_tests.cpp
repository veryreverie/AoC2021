#include <gtest/gtest.h>
#include "14.hpp"

TEST(Day14, day14){
  std::vector<std::string> input = {
    "NNCB",
    "",
    "CH -> B",
    "HH -> N",
    "CB -> H",
    "NH -> C",
    "HB -> C",
    "HC -> B",
    "HN -> C",
    "NN -> C",
    "BH -> H",
    "NC -> B",
    "NB -> B",
    "BN -> B",
    "BB -> N",
    "BC -> B",
    "CC -> N",
    "CN -> C"
  };
  
  const auto [result1, result2] = day14(input);
  
  EXPECT_EQ(result1, 1588);
  EXPECT_EQ(result2, 2188189693529);
}
