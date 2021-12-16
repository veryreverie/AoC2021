#include "11.hpp"

namespace Day11{
  class Octopus{
    public:
      int x;
      int y;
      int brightness;
      bool flashed;
      
      Octopus(const int& _x, const int& _y, const int& _brightness);
      friend std::ostream& operator<<(std::ostream& os, const Octopus& octopus);
  };

  Octopus::Octopus(const int& _x, const int& _y, const int& _brightness){
    x = _x;
    y = _y;
    brightness = _brightness;
    flashed = false;
  }

  std::ostream& operator<<(std::ostream& os, const Octopus& octopus){
    return os << octopus.brightness;
  }

  class Octopi{
    public:
      std::vector<std::vector<Octopus>> octopi;
      int flashes;
      
      Octopi();
      friend std::ostream& operator<<(std::ostream& os, const Octopi& octopi);
      Octopi(const std::vector<std::string>& flines);
      
      std::vector<Octopus> neighbours(const Octopus& octopus) const;
      void increase(const Octopus& _octopus);
      void flash(const Octopus& _octopus);
      void step();
  };

  Octopi::Octopi(){
    flashes = 0;
  }

  std::ostream& operator<<(std::ostream& os, const Octopi& octopi){
    for (const auto& row : octopi.octopi){
      for (const auto& octopus : row){
        os << octopus;
      }
      os << std::endl;
    }
    return os;
  }

  Octopi::Octopi(const std::vector<std::string>& flines) : Octopi() {
    int x = -1;
    for (const auto& fline : flines){
      x++;
      octopi.push_back({});
      int y = -1;
      for (const char& c : fline){
        y++;
        octopi.back().push_back(Octopus(x, y, c-'0'));
      }
    }
  }

  std::vector<Octopus> Octopi::neighbours(const Octopus& octopus) const {
    std::vector<Octopus> result;
    for (int i=octopus.x-1; i<=octopus.x+1; ++i){
      if (i>=0 and i<octopi.size()){
        for (int j=octopus.y-1; j<=octopus.y+1; ++j){
          if (j>=0 and j<octopi[0].size()){
            result.push_back(octopi[i][j]);
          }
        }
      }
    }
    return result;
  }

  void Octopi::increase(const Octopus& _octopus){
    Octopus& octopus = octopi[_octopus.x][_octopus.y];
    if (not octopus.flashed){
      octopus.brightness++;
      if (octopus.brightness==10){
        flash(octopus);
      }
    }
  }

  void Octopi::flash(const Octopus& _octopus){
    Octopus& octopus = octopi[_octopus.x][_octopus.y];
    octopus.brightness = 0;
    octopus.flashed = true;
    flashes++;
    for (const auto& neighbour : neighbours(octopus)){
      increase(neighbour);
    }
  }

  void Octopi::step(){
    for (const auto& row : octopi){
      for (const auto& octopus : row){
        increase(octopus);
      }
    }
    for (auto& row : octopi){
      for (auto& octopus : row){
        octopus.flashed = false;
      }
    }
  }

  std::tuple<long long,long long> day11(const std::vector<std::string>& flines){
    Octopi octopi(flines);
    for (int i=0; i<100; ++i){
      octopi.step();
    }
    int first_flashes = octopi.flashes;
    
    int step=100;
    for (;;){
      step++;
      octopi.flashes = 0;
      octopi.step();
      if (octopi.flashes == 100){
        break;
      }
    }
    return {first_flashes, step};
  }
}
