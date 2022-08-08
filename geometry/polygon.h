#include "ray.h"

#pragma once
namespace geometry {
class Polygon : public IShape {
 public:
  std::vector<Point> mas_;
  Polygon() = default;
  explicit Polygon(const std::vector<Point>& v) {
    for (size_t i = 0; i < v.size(); ++i) {
      mas_.push_back(v[i]);
    }
  }
  Polygon& Move(const Vector&) override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  Polygon* Clone() const override;
  std::string ToString() const override;
};
}  // namespace geometry
