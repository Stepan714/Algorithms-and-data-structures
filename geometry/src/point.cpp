#include "../point.h"
#include "../vector.h"
#include "../segment.h"

namespace geometry {

Vector operator-(const Point &a, const Point &b) {
  Vector ab(b, a);
  return ab;
}

bool Point::CrossesSegment(const Segment &sv) const {
  Vector v1(sv.p1_, *this);
  Vector v2(sv.p1_, sv.p2_);
  int64_t x_min = sv.p1_.x > sv.p2_.x ? sv.p2_.x : sv.p1_.x;
  int64_t x_max = sv.p1_.x < sv.p2_.x ? sv.p2_.x : sv.p1_.x;
  int64_t y_min = sv.p1_.y > sv.p2_.y ? sv.p2_.y : sv.p1_.y;
  int64_t y_max = sv.p1_.y < sv.p2_.y ? sv.p2_.y : sv.p1_.y;
  bool flag = false;
  if (VectorPr(v1, v2) == 0 && x >= x_min && x <= x_max && y >= y_min && y <= y_max) {
    flag = true;
  }
  return flag;
}

Point &Point::Move(const Vector &v) {  // for Point
  x += (v.p2_.x - v.p1_.x);
  y += (v.p2_.y - v.p1_.y);
  return *this;
}

std::string Point::ToString() const {  // for Point
  std::string s, d;
  s = "Point(";
  int64_t t = x;
  d = DoString(x);
  s += d;
  s += ", ";
  t = y;
  d = DoString(t);
  s += d;
  s += ")";
  return s;
}

Point *Point::Clone() const {
  return (new Point(x, y));
}

bool Point::ContainsPoint(const Point &p) const {
  bool flag = false;
  if (p.x == x && p.y == y) {
    flag = true;
  }
  return flag;
}
}  // namespace geometry
