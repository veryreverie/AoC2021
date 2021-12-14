#include "12.hpp"

class Input{
  public:
    std::vector<std::string> cave_names;
    
    friend std::ostream& operator<<(std::ostream& os, const Input& input);
    Input(const std::string& fline);
};

std::ostream& operator<<(std::ostream& os, const Input& input){
  return os << input.cave_names[0] << '-' << input.cave_names[1];
}

Input::Input(const std::string& fline){
  std::istringstream iss(fline);
  std::string token;
  while (std::getline(iss, token, '-')){
    cave_names.push_back(token);
  }
}

class Cave{
  public:
    std::string name;
    bool big;
    std::map<std::string,int> neighbours;
    
    Cave(const std::string& _name);
    
    friend std::ostream& operator<<(std::ostream& os, const Cave& cave);
    
    void add_neighbour(const Cave& neighbour);
};

Cave::Cave(const std::string& _name){
  name = _name;
  big = std::isupper(name[0])!=0;
}

std::ostream& operator<<(std::ostream& os, const Cave& cave){
  os << cave.name << " " << cave.big << " |";
  for (const auto& [neighbour,weight] : cave.neighbours){
    os << " " << neighbour << " " << weight;
  }
  return os;
}

void Cave::add_neighbour(const Cave& neighbour){
  try {
    neighbours.at(neighbour.name)++;
  } catch(const std::out_of_range& e){
    neighbours.insert({neighbour.name, 1});
  }
}

class Caves{
  public:
    std::map<std::string,Cave> caves;
    
    Caves(const std::vector<Input>& inputs);
};

Caves::Caves(const std::vector<Input>& inputs){
  std::map<std::string,Cave> big_caves;
  
  for (const auto& input : inputs){
    for (const auto& cave_name : input.cave_names){
      Cave cave(cave_name);
      auto& map = cave.big ? big_caves : caves;
      try{
        map.at(cave_name);
      } catch(const std::out_of_range& e){
        map.insert({cave_name, cave});
      }
    }
    
    Cave a(input.cave_names[0]);
    Cave b(input.cave_names[1]);
    if (a.big){
      big_caves.at(a.name).add_neighbour(b);
    } else if (b.big){
      big_caves.at(b.name).add_neighbour(a);
    } else {
      caves.at(a.name).add_neighbour(b);
      caves.at(b.name).add_neighbour(a);
    }
  }
  
  for ([[maybe_unused]] const auto& [big_name, big_cave] : big_caves){
    for ([[maybe_unused]] const auto& [name1, weight1] : big_cave.neighbours){
      for ([[maybe_unused]] const auto& [name2, weight2] : big_cave.neighbours){
        caves.at(name1).add_neighbour(Cave(name2));
      }
    }
  }
}

class Path{
  public:
    std::vector<std::string> steps;
    long long weight;
    bool double_visit;
    
    Path(const std::vector<std::string>& _steps, const long long& _weight);
    
    friend std::ostream& operator<<(std::ostream& os, const Path& path);
    
    bool done() const;
    std::tuple<std::vector<Path>, long long>
    continuations(const Caves& caves, const bool& double_visit_allowed) const;
};

Path::Path(const std::vector<std::string>& _steps, const long long& _weight){
  steps = _steps;
  weight = _weight;
  double_visit = false;
}

std::ostream& operator<<(std::ostream& os, const Path& path){
  for (const auto& step : path.steps){
    os << step << " ";
  }
  return os << path.weight;
}

std::tuple<std::vector<Path>, long long>
Path::continuations(const Caves& caves, const bool& double_visit_allowed) const{
  std::vector<Path> new_paths;
  long long done_paths = 0;
  const Cave last = caves.caves.at(steps[steps.size()-1]);
  for (const auto& [neighbour, neighbour_weight] : last.neighbours){
    Path new_path = *this;
    new_path.steps.push_back(neighbour);
    new_path.weight *= neighbour_weight;
    
    if (item_in_list(neighbour, steps)){
      if (not double_visit_allowed or new_path.double_visit){
        continue;
      }
      new_path.double_visit = true;
    }
    
    if (neighbour=="end"){
      done_paths += new_path.weight;
    } else if (neighbour!="start") {
      new_paths.push_back(new_path);
    }
  }
  return {new_paths, done_paths};
}

long long count_paths(const Caves& caves, const int& max_visits){
  long long result = 0;
  std::vector<Path> old_paths;
  old_paths.push_back(Path({"start"}, 1));
  while (old_paths.size()>0){
    std::vector<Path> new_paths;
    for (const auto& path : old_paths){
      const auto [new_new_paths, new_done_paths] = path.continuations(caves, max_visits);
      new_paths.insert(new_paths.end(), new_new_paths.begin(), new_new_paths.end());
      result += new_done_paths;
    }
    old_paths = new_paths;
  }
  
  return result;
}

std::tuple<long long,long long> day12(const std::vector<std::string>& flines){
  std::vector<Input> inputs;
  for (const auto& fline : flines){
    inputs.push_back(Input(fline));
  }
  
  Caves caves(inputs);
  
  return {count_paths(caves, false), count_paths(caves, true)};
}
