#include "04.hpp"

namespace Day04{
  class Calls{
    public:
      std::vector<int> calls;
      
      friend std::ostream& operator<<(std::ostream& os, const Calls& calls);
      friend std::istream& operator>>(std::istream& is, Calls& calls);
      Calls(const std::string& line);
  };

  std::ostream& operator<<(std::ostream& os, const Calls& calls){
    for (const auto call : calls.calls){
      os << call << ',';
    }
    return os;
  }

  std::istream& operator>>(std::istream& is, Calls& calls){
    int call;
    while (is >> call){
      calls.calls.push_back(call);
      is >> Common::Ignore(1,',');
    }
    return is;
  }

  Calls::Calls(const std::string& line){
    std::istringstream(line) >> *this;
  }

  class Box{
    public:
      int number;
      bool mark;
      
      Box();
      
      friend std::ostream& operator<<(std::ostream& os, const Box& box);
      friend std::istream& operator>>(std::istream& is, Box& box);
      Box(const std::string& s);
  };

  Box::Box(){
  }

  std::ostream& operator<<(std::ostream& os, const Box& box){
    if (box.mark){
      os << '-';
    } else {
      os << '+';
    }
    return os << std::setw(2) << std::setfill('0') << box.number;
  }

  std::istream& operator>>(std::istream& is, Box& box){
    is >> box.number;
    box.mark = box.number<=0;
    return is;
  }

  Box::Box(const std::string& s){
    std::istringstream(s) >> *this;
  }

  class Bingo{
    public:
      std::vector<std::vector<Box>> boxes;
      bool won;
      
      friend std::ostream& operator<<(std::ostream& os, const Bingo& bingo);
      Bingo(std::vector<std::string> lines);
      
      void call(const int& number);
      bool wins();
      int score();
  };

  std::ostream& operator<<(std::ostream& os, const Bingo& bingo){
    for (const auto& line : bingo.boxes){
      for (const auto& box : line){
        os << box << ' ';
      }
      os << std::endl;
    }
    return os;
  }

  Bingo::Bingo(std::vector<std::string> lines){
    for (const auto& line : lines){
      boxes.push_back({});
      std::istringstream iss(line);
      Box box;
      while (not iss.eof()){
        iss >> box;
        boxes.back().push_back(box);
      }
    }
    won = false;
  }

  void Bingo::call(const int& number){
    if (won){
      return;
    }
    
    for (auto& row : boxes){
      for (auto& box : row){
        if (box.number==number){
          box.mark = true;
          if (wins()){
            won = true;
          }
          return;
        }
      }
    }
  }

  bool Bingo::wins(){
    bool result;
    
    for (const auto& row : boxes){
      result = true;
      for (const auto& box : row){
        if (not box.mark){
          result = false;
          break;
        }
      }
      if (result){
        return result;
      }
    }
    
    for (int i=0; i<boxes[0].size(); ++i){
      result = true;
      for (const auto& row : boxes){
        if (not row[i].mark){
          result = false;
          break;
        }
      }
      if (result){
        return result;
      }
    }
    
    return result;
  }

  int Bingo::score(){
    int result = 0;
    for (const auto& row : boxes){
      for (const auto& box : row){
        if (not box.mark){
          result += box.number;
        }
      }
    }
    return result;
  }

  std::tuple<long long,long long> day04(const std::vector<std::string>& flines){
    Calls calls(flines[0]);
    
    std::vector<Bingo> bingos;
    for (int i=0; i<flines.size()/6; ++i){
      bingos.push_back(Bingo(std::vector<std::string>(&flines[6*i+2],&flines[6*i+7])));
    }
    
    std::vector<int> scores;
    for (const auto& call : calls.calls){
      for (auto& bingo : bingos){
        bool won_previously = bingo.won;
        bingo.call(call);
        if ((not won_previously) and bingo.won) {
          scores.push_back(bingo.score() * call);
        }
      }
    }
    
    return {scores[0], scores.back()};
  }
}
