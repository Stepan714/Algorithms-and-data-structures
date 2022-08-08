#include "point.h"
#include "vector.h"

#pragma once
namespace geometry {
class Segment : public IShape {
 public:
  Point p1_;
  Point p2_;
  Segment() = default;
  Segment(const Point& p1, const Point& p2) {
    p1_.x = p1.x;
    p1_.y = p1.y;
    p2_.x = p2.x;
    p2_.y = p2.y;
  }
  friend std::istream& operator>>(std::istream& in, Segment& s) {
    in >> s.p1_.x >> s.p1_.y >> s.p2_.x >> s.p2_.y;
    return in;
  }
  friend std::ostream& operator<<(std::ostream& out, const Segment& s) {
    out << s.p1_.x << s.p1_.y << s.p2_.x << s.p2_.y << "\n";
    return out;
  }
  Segment& Move(const Vector&) override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  Segment* Clone() const override;
  std::string ToString() const override;
};
}  // namespace geometry
