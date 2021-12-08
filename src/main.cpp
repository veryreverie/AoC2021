#include "common.hpp"
#include "01.hpp"
#include "02.hpp"
#include "03.hpp"
#include "04.hpp"
#include "05.hpp"
#include "06.hpp"
#include "07.hpp"
#include "08.hpp"

void abort(){
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
    abort();
  }
  std::string arg(argv[1]);
  if (arg=="-h" or arg=="--help"){
    help();
  }
  int day;
  try {
    day = std::stoi(arg);
  } catch (const std::invalid_argument& e){
    abort();
  }
  
  std::string filename = make_filename(day);
  std::vector<std::string> flines = read_input_file(filename);
  
  std::vector<std::function<
    std::tuple<long long,long long>(const std::vector<std::string>&)
  >> functions({day01, day02, day03, day04, day05, day06, day07, day08});
  auto [output1, output2] = functions[day-1](flines);
  std::cout << output1 << std::endl;
  std::cout << output2 << std::endl;
}
