#include "15.hpp"

namespace Day15{
  class Point{
    public:
      int x;
      int y;
      int risk;
      
      Point(const int& _x, const int& _y, const int& risk);
      
      friend std::ostream& operator<<(std::ostream& os, const Point& point);
  };

  Point::Point(const int& _x, const int& _y, const int& _risk){
    x = _x;
    y = _y;
    risk = _risk;
  }
  
  std::ostream& operator<<(std::ostream& os, const Point& point){
    return os << point.x << " " << point.y << " " << point.risk;
  }
  
  struct PointCompare
  {
    bool operator() (const Point& lhs, const Point& rhs) const {
      if (lhs.x!=rhs.x){
        return lhs.x<rhs.x;
      } else {
        return lhs.y<rhs.y;
      }
    }
  };

  class Grid{
    public:
      std::vector<std::vector<Point>> points;
      
      Grid(const std::vector<std::string>& lines, const int& repeats);
      
      friend std::ostream& operator<<(std::ostream& os, const Grid& grid);
      
      std::vector<Point> neighbours(const Point& point) const;
  };

  Grid::Grid(const std::vector<std::string>& lines, const int& repeats){
    int x=-1;
    for (int i=0; i<repeats; ++i){
      for (const auto& line : lines){
        x++;
        points.push_back({});
        int y=-1;
        for (int j=0; j<repeats; ++j){
          for (const char& c : line){
            y++;
            points[points.size()-1].push_back(Point(x,y,((c-'0')+i+j-1)%9+1));
          }
        }
      }
    }
  }
  
  std::ostream& operator<<(std::ostream& os, const Grid& grid){
    for (const auto& row : grid.points){
      for (const auto& point : row){
        os << point.risk;
      }
      os << std::endl;
    }
    return os;
  }
  
  std::vector<Point> Grid::neighbours(const Point& point) const{
    std::vector<Point> result;
    if (point.x>0){
      result.push_back(points[point.x-1][point.y]);
    }
    if (point.x<points.size()-1){
      result.push_back(points[point.x+1][point.y]);
    }
    if (point.y>0){
      result.push_back(points[point.x][point.y-1]);
    }
    if (point.y<points[0].size()-1){
      result.push_back(points[point.x][point.y+1]);
    }
    return result;
  }
  
  class RiskMap{
    public:
      std::vector<std::vector<int>> risks;
      
      RiskMap(const Grid& grid);
      
      friend std::ostream& operator<<(std::ostream& os, const RiskMap& risk_map);
  };
  
  RiskMap::RiskMap(const Grid& grid){
    for (const auto& row : grid.points){
      risks.push_back(std::vector(row.size(), -1));
    }
    
    std::map<Point, int, PointCompare> candidates;
    candidates.insert({grid.points[0][0], 0});
    
    while (candidates.size()>0){
      auto it = Common::min_map_value(candidates);
      auto [point, risk] = *it;
      candidates.erase(it);
      
      risks[point.x][point.y] = risk;
      
      for (const auto& neighbour : grid.neighbours(point)){
        if (risks[neighbour.x][neighbour.y] == -1){
          try{
            candidates.at(neighbour);
          } catch(const std::out_of_range& e) {
            candidates.insert({neighbour, risk+neighbour.risk});
          }
        }
      }
    }
  }
  
  std::ostream& operator<<(std::ostream& os, const RiskMap& risk_map){
    for (const auto& row : risk_map.risks){
      for (const auto& risk : row){
        os << risk << " ";
      }
      os << std::endl;
    }
    return os;
  }
  
  int calculate_risk(const std::vector<std::string>& flines, const int& repeats){
    Grid grid(flines, repeats);
    RiskMap risk_map(grid);
    return risk_map.risks[risk_map.risks.size()-1][risk_map.risks[0].size()-1];
  }

  std::tuple<long long,long long> day15(const std::vector<std::string>& flines){
    return {calculate_risk(flines, 1), calculate_risk(flines, 5)};
  }
}
