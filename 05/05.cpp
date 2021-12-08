#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <exception>
#include <iomanip>

template <class T>
T munch(std::istringstream& iss, char delim) {
  std::string token;
  std::getline(iss, token, delim);
  T result;
  std::istringstream(token) >> result;
  return result;
}

template <class T>
std::vector<T> split(const std::string& s, char delim) {
  std::istringstream iss(s);
  std::vector<T> result;
  while (not iss.eof()){
    result.push_back(munch<T>(iss, delim));
  }
  return result;
}

class Line{
  public:
    std::vector<int> start;
    std::vector<int> end;
    
    Line();
    
    friend std::ostream& operator<<(std::ostream& os, const Line& line);
    friend std::istream& operator>>(std::istream& is, Line& line);
    Line(const std::string& s);
    
    bool grid_aligned() const;
};

Line::Line(){
}

std::ostream& operator<<(std::ostream& os, const Line& line){
  os << line.start[0] << ',' << line.start[1];
  os << " -> ";
  os << line.end[0] << ',' << line.end[1];
  return os;
}

std::istream& operator>>(std::istream& is, Line& line){
  std::string token;
  is >> token;
  line.start = split<int>(token, ',');
  is >> token;
  is >> token;
  line.end = split<int>(token, ',');
  return is;
}

Line::Line(const std::string& s){
  std::istringstream(s) >> *this;
}

bool Line::grid_aligned() const{
  return start[0]==end[0] or start[1]==end[1];
}

class Grid{
  public:
    std::vector<std::vector<int>> squares;
    
    Grid(std::vector<int> max);
    
    void lay(const Line& line);
    int count_intersections() const;
};

Grid::Grid(std::vector<int> max){
  std::vector<int> row;
  for (int i=0; i<=max[1]; ++i){
    row.push_back(0);
  }
  for (int i=0; i<=max[0]; ++i){
    squares.push_back(row);
  }
}

void Grid::lay(const Line& line){
  std::vector<int> delta({0,0});
  for (int i=0; i<2; i++){
    if (line.end[i]>line.start[i]){
      delta[i] = 1;
    } else if (line.end[i]==line.start[i]){
      delta[i] = 0;
    } else {
      delta[i] = -1;
    }
  }
  
  for (int i=line.start[0],j=line.start[1];
       i*delta[0]<=line.end[0]*delta[0] and j*delta[1]<=line.end[1]*delta[1];
       i+=delta[0],j+=delta[1]){
    squares[i][j]++;
  }
}

int Grid::count_intersections() const{
  int result = 0;
  for (const auto& row : squares){
    for (const auto& square : row){
      if (square>=2){
        result++;
      }
    }
  }
  return result;
}

void day05(std::vector<std::string> flines){
  std::vector<Line> lines;
  for (const auto& fline : flines){
    lines.push_back(Line(fline));
  }
  
  std::vector<int> min = {0, 0};
  std::vector<int> max = {0, 0};
  for (const auto& line : lines){
    min[0] = std::min(min[0],line.start[0]);
    min[1] = std::min(min[1],line.start[1]);
    max[0] = std::max(max[0],line.start[0]);
    max[1] = std::max(max[1],line.start[1]);
  }
  
  Grid grid(max);
  
  for (const auto& line : lines){
    if (line.grid_aligned()){
      grid.lay(line);
    }
  }
  
  std::cout << grid.count_intersections() << std::endl;
  
  for (const auto& line : lines){
    if (not line.grid_aligned()){
      grid.lay(line);
    }
  }
  
  std::cout << grid.count_intersections() << std::endl;
}

int main(void){
  std::ifstream infile("input");
  std::vector<std::string> lines;
  if (infile.is_open()){
    std::string line;
    while (getline(infile, line)){
      lines.push_back(line);
    }
  }
  infile.close();
  
  day05(lines);
}