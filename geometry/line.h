#include "segment.h"

#pragma once
namespace geometry {
class Line : public IShape {
 public:
  Point p1_;
  Point p2_;
  Vector v_;
  Line() = default;
  Line(const Point& p1, const Point& p2);
  explicit Line(const Segment& sv);
  friend std::istream& operator>>(std::istream& in, Line& l) {
    in >> l.p1_.x >> l.p1_.y >> l.p2_.x >> l.p2_.y;
    l.v_.p1_.x = l.p1_.x;
    l.v_.p1_.y = l.p1_.y;
    l.v_.p2_.x = l.p2_.x;
    l.v_.p2_.y = l.p2_.y;
    return in;
  }
  friend std::ostream& operator<<(std::ostream& out, const Line& l) {
    out << l.p1_.x << l.p1_.y << l.p2_.x << l.p2_.y << "\n";
    return out;
  }
  Line& Move(const Vector&) override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  Line* Clone() const override;
  std::string ToString() const override;
};
}  // namespace geometry
