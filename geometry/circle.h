#include "point.h"
#include "vector.h"
#include "segment.h"

#pragma once
namespace geometry {
class Circle : public IShape {
 public:
  Point o_;
  int64_t r_;
  Circle() = default;
  Circle(const Point& o, int64_t r) : IShape(), o_(o), r_(r) {
  }
  Circle& Move(const Vector&) override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  Circle* Clone() const override;
  std::string ToString() const override;
  // operators overloading
  friend std::istream& operator>>(std::istream& in, Circle& c) {
    in >> c.o_.x >> c.o_.y >> c.r_;
    return in;
  }
};
}  // namespace geometry
