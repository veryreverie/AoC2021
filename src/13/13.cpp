#include "13.hpp"

enum class Axis {x, y};

std::ostream& operator<<(std::ostream& os, const Axis& axis){
  if (axis==Axis::x){
    return os << 'x';
  } else {
    return os << 'y';
  }
}

std::istream& operator>>(std::istream& is, Axis& axis){
  char c;
  is >> c;
  if (c=='x'){
    axis = Axis::x;
  } else if (c=='y') {
     axis = Axis::y;
  } else {
    throw std::invalid_argument({c});
  }
  return is;
}

class Symmetry{
  public:
    Axis axis;
    int offset;
    
    friend std::ostream& operator<<(std::ostream& os, const Symmetry& symmetry);
    friend std::istream& operator>>(std::istream& is, Symmetry& symmetry);
    Symmetry(const std::string& string);
};

std::ostream& operator<<(std::ostream& os, const Symmetry& symmetry){
  return os << "fold along " << symmetry.axis << '=' << symmetry.offset;
}

std::istream& operator>>(std::istream& is, Symmetry& symmetry){
  return is >> Ignore(11) >> symmetry.axis >> Ignore(1,'=') >> symmetry.offset;
}

Symmetry::Symmetry(const std::string& string){
  std::istringstream(string) >> *this;
}

class Dot{
  public:
    int x;
    int y;
    
    friend std::ostream& operator<<(std::ostream& os, const Dot& dot);
    friend std::istream& operator>>(std::istream& is, Dot& dot);
    Dot(const std::string& string);
    
    void act(const Symmetry& symmetry);
};

std::ostream& operator<<(std::ostream& os, const Dot& dot){
  return os << dot.x << ',' << dot.y;
}

std::istream& operator>>(std::istream& is, Dot& dot){
  return is >> dot.x >> Ignore(1,',') >> dot.y;
}

Dot::Dot(const std::string& string){
  std::istringstream(string) >> *this;
}

void Dot::act(const Symmetry& symmetry){
  if (symmetry.axis==Axis::x){
    x = std::min(x, 2*symmetry.offset-x);
  } else {
    y = std::min(y, 2*symmetry.offset-y);
  }
}

class Dotboard{
  public:
    std::set<std::tuple<int,int>> dotboard;
    
    Dotboard(const std::vector<Dot>& dots);
    
    friend std::ostream& operator<<(std::ostream& os, const Dotboard& dotboard);
    
    int count() const;
};

Dotboard::Dotboard(const std::vector<Dot>& dots){
  for (const auto& dot : dots){
    dotboard.insert({dot.x,dot.y});
  }
}

std::ostream& operator<<(std::ostream& os, const Dotboard& dotboard){
  int max_x = 0;
  int max_y = 0;
  for (const auto& [x,y] : dotboard.dotboard){
    max_x = std::max(max_x,x);
    max_y = std::max(max_y,y);
  }
  
  for (int y=0; y<=max_y; ++y){
    for (int x=0; x<=max_x; ++x){
      if (item_in_list(std::tuple(x,y), dotboard.dotboard)) {
        os << '#';
      } else {
        os << '.';
      }
    }
    os << std::endl;
  }
  return os;
}

int Dotboard::count() const{
  return dotboard.size();
}

std::tuple<long long,long long> day13(const std::vector<std::string>& flines){
  auto it = std::find(flines.begin(), flines.end(), "");
  std::vector<Dot> dots(flines.begin(), it);
  std::vector<Symmetry> symmetries(it+1, flines.end());
  
  std::vector<Dot> first_dots(dots);
  for (auto& dot : first_dots){
    dot.act(symmetries[0]);
  }
  Dotboard dotboard(first_dots);
  int count1 = dotboard.count();
  
  for (auto& dot : dots){
    for (const auto& symmetry : symmetries){
      dot.act(symmetry);
    }
  }
  std::cout << Dotboard(dots);
  
  return {count1, 0};
}
