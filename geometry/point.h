#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>

#pragma once
namespace geometry {
class Vector;
class Point;
class Segment;
class Line;
class Ray;
class Polygon;
class Circle;
class IShape {
 public:
  IShape() = default;
  virtual ~IShape() = default;
  virtual bool ContainsPoint(const Point&) const = 0;
  virtual IShape& Move(const Vector&) = 0;
  virtual bool CrossesSegment(const Segment&) const = 0;
  virtual IShape* Clone() const = 0;
  virtual std::string ToString() const = 0;
};

class Point : public IShape {
 public:
  int64_t x;
  int64_t y;
  Point() : IShape(), x(0), y(0) {
  }
  Point(int64_t x, int64_t y) : IShape(), x(x), y(y) {
  }
  Point(const Point& p) : IShape(), x(p.x), y(p.y) {
  }
  //~Point() override = default;
  friend std::istream& operator>>(std::istream& in, Point& p) {
    in >> p.x >> p.y;
    return in;
  }
  friend std::ostream& operator<<(std::ostream& out, const Point& p) {
    out << p.x << " " << p.y;
    return out;
  }
  Point& operator=(const Point& p) {
    x = p.x;
    y = p.y;
    return *this;
  }
  friend Vector operator-(const Point&, const Point&);
  bool CrossesSegment(const Segment& sv) const override;
  Point& Move(const Vector&) override;
  bool ContainsPoint(const Point& p) const override;
  Point* Clone() const override;
  std::string ToString() const override;
};
template <typename T>
std::string DoString(T val) {
  std::ostringstream oss;
  oss << val;
  return oss.str();
}
}  // namespace geometry
