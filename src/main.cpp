#include "common.hpp"
#include "01.hpp"
#include "02.hpp"
#include "03.hpp"
#include "04.hpp"
#include "05.hpp"
#include "06.hpp"
#include "07.hpp"
#include "08.hpp"
#include "09.hpp"
#include "10.hpp"
#include "11.hpp"
#include "12.hpp"
#include "13.hpp"
#include "14.hpp"
#include "15.hpp"
#include "16.hpp"
#include "17.hpp"
#include "18.hpp"
#include "19.hpp"
#include "20.hpp"
#include "21.hpp"
#include "22.hpp"
#include "23.hpp"
#include "24.hpp"
#include "25.hpp"

void input_abort(){
  std::cout << "Bad input. Please call `aoc -h` for help." << std::endl;
  exit(1);
}

void help(){
  std::cout << "aoc day" << std::endl;
  std::cout << std::endl;
  std::cout << "`day` should be an integer in 1...24 inclusive." << std::endl;
  exit(0);
}

std::string make_filename(const int& day){
  std::ostringstream oss;
  oss << "input_" << std::setw(2) << std::setfill('0') << day;
  return oss.str();
}

int main(int argc, char* argv[]){
  if (argc!=2){
    input_abort();
  }
  std::string arg(argv[1]);
  if (arg=="-h" or arg=="--help"){
    help();
  }
  int day;
  try {
    day = std::stoi(arg);
  } catch (const std::invalid_argument& e){
    input_abort();
  }
  
  std::string filename = make_filename(day);
  std::vector<std::string> flines = Common::read_file(filename);
  
  using func = std::function<
    std::tuple<long long,long long>(const std::vector<std::string>&)
  >;
  std::vector<func> functions({
    Day01::day01,
    Day02::day02,
    Day03::day03,
    Day04::day04,
    Day05::day05,
    Day06::day06,
    Day07::day07,
    Day08::day08,
    Day09::day09,
    Day10::day10,
    Day11::day11,
    Day12::day12,
    Day13::day13,
    Day14::day14,
    Day15::day15,
    Day16::day16,
    Day17::day17,
    Day18::day18,
    Day19::day19,
    Day20::day20,
    Day21::day21,
    Day22::day22,
    Day23::day23,
    Day24::day24,
    Day25::day25
  });
  auto [output1, output2] = functions[day-1](flines);
  std::cout << output1 << std::endl;
  std::cout << output2 << std::endl;
}
