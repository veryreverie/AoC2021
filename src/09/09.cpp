#include "09.hpp"

class Point{
  public:
    int x;
    int y;
    int z;
    int basin;
    
    Point(const int& _x, const int& _y, const int& _z);
    
    template <class T>
    bool is_minimum(const T& neighbours) const;
};

Point::Point(const int& _x, const int& _y, const int& _z){
  x = _x;
  y = _y;
  z = _z;
  basin = -1;
}

template <class T>
bool Point::is_minimum(const T& neighbours) const {
  for (const Point& neighbour : neighbours){
    if (z>=neighbour.z){
      return false;
    }
  }
  return true;
}

class Heightmap{
  public:
    std::vector<std::vector<Point>> points;
    std::vector<int> basin_sizes;
    
    Heightmap();
    
    Heightmap(const std::vector<std::string>& lines);
    
    std::vector<Point> get_neighbours(const Point& point) const;
    std::vector<Point> low_points() const;
    void fill_basin(const Point& _point, const int& basin);
};

Heightmap::Heightmap(){
}

Heightmap::Heightmap(const std::vector<std::string>& lines){
  int x=-1;
  for (const auto& line : lines){
    x++;
    points.push_back({});
    int y=-1;
    for (const char& c : line){
      y++;
      points[points.size()-1].push_back(Point(x,y,c-'0'));
    }
  }
}

std::vector<Point> Heightmap::get_neighbours(const Point& point) const {
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

std::vector<Point> Heightmap::low_points() const {
  std::vector<Point> result;
  for (const auto& row : points){
    for (const auto& point : row){
      if (point.is_minimum(get_neighbours(point))){
        result.push_back(point);
      }
    }
  }
  return result;
}

void Heightmap::fill_basin(const Point& _point, const int& basin){
  Point& point = points[_point.x][_point.y];
  if (point.z==9 or point.basin==basin){
    return;
  }
  point.basin = basin;
  if (basin_sizes.size()<=basin){
    basin_sizes.push_back(1);
  } else {
    basin_sizes[basin]++;
  }
  for (Point& neighbour : get_neighbours(point)){
    fill_basin(neighbour, basin);
  }
}

std::tuple<long long,long long> day09(const std::vector<std::string>& flines){
  Heightmap heightmap(flines);
  auto low_points = heightmap.low_points();
  
  int risk_levels = 0;
  for (const Point& point : low_points){
    risk_levels += 1+point.z;
  }
  
  int num_basins = -1;
  std::vector<int> basin_sizes;
  for (Point& point : low_points){
    num_basins++;
    heightmap.fill_basin(point, num_basins);
  }
  std::vector<int> sorted_sizes(heightmap.basin_sizes);
  std::sort(sorted_sizes.begin(), sorted_sizes.end());
  int basin_product = std::accumulate(
    sorted_sizes.end()-3,
    sorted_sizes.end(),
    1,
    std::multiplies<int>());
  
  return {risk_levels, basin_product};
}
