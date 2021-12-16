#include <gtest/gtest.h>
#include "16.hpp"

TEST(Day16, day16){
  std::map<std::string,int> part_1{
    {"8A004A801A8002F478", 16},
    {"620080001611562C8802118E34", 12},
    {"C0015000016115A2E0802F182340", 23},
    {"A0016C880162017C3686B18A3D4780", 31}
  };
  for (const auto& [input, output] : part_1){
    [[maybe_unused]] const auto [result1, result2] = Day16::day16({input});
    EXPECT_EQ(result1, output);
  }
  
  std::map<std::string,int> part_2{
    {"C200B40A82", 3},
    {"04005AC33890", 54},
    {"880086C3E88112", 7},
    {"CE00C43D881120", 9},
    {"D8005AC2A8F0", 1},
    {"F600BC2D8F", 0},
    {"9C005AC2F8F0", 0},
    {"9C0141080250320F1802104A08", 1}
  };
  for (const auto& [input, output] : part_2){
    [[maybe_unused]] const auto [result1, result2] = Day16::day16({input});
    EXPECT_EQ(result2, output);
  }
}
