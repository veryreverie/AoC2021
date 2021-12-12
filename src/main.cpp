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

std::vector<std::string> read_input_file(const std::string& filename){
  std::ifstream infile(filename);
  std::vector<std::string> flines;
  if (infile.is_open()){
    std::string fline;
    while (getline(infile, fline)){
      flines.push_back(fline);
    }
  }
  infile.close();
  
  return flines;
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
  std::vector<std::string> flines = read_input_file(filename);
  
  std::vector<std::function<
    std::tuple<long long,long long>(const std::vector<std::string>&)
  >> functions({day01, day02, day03, day04, day05, day06, day07, day08, day09, day10, day11, day12, day13, day14, day15, day16, day17, day18, day19, day20, day21, day22, day23, day24, day25});
  auto [output1, output2] = functions[day-1](flines);
  std::cout << output1 << std::endl;
  std::cout << output2 << std::endl;
}
