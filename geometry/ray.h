
#include "line.h"

#pragma once
namespace geometry {
class Ray : public IShape {
 public:
  Point o_;
  Vector v_;
  Ray() = default;
  Ray(const Point& p, const Vector& v) : IShape(), o_(p), v_(v) {
  }
  Ray(const Point& p1, const Point& p2) : IShape(), o_(p1), v_(p1, p2) {
  }
  Ray& Move(const Vector&) override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  Ray* Clone() const override;
  std::string ToString() const override;
  friend std::istream& operator>>(std::istream& in, Ray& r) {
    in >> r.o_.x >> r.o_.y >> r.v_.p2_.x >> r.v_.p2_.y;
    r.v_.p1_.x = r.o_.x;
    r.v_.p1_.y = r.o_.y;
    return in;
  }
};
}  // namespace geometry
