#include "../circle.h"
#include "../point.h"
#include "../vector.h"
namespace geometry {
Circle &Circle::Move(const Vector &rv) {
  o_.Move(rv);
  return *this;
}

bool Circle::ContainsPoint(const Point &p) const {
  bool flag = false;
  if (Mod(p, o_) <= 1.0 * r_) {
    flag = true;
  }
  return flag;
}

bool Circle::CrossesSegment(const Segment &sv) const {
  bool flag = false;
  if (Mod(o_, sv.p1_) <= 1.0 * r_ && Mod(o_, sv.p2_) >= 1.0 * r_) {
    flag = true;
  } else if (Mod(o_, sv.p1_) >= 1.0 * r_ && Mod(o_, sv.p2_) <= 1.0 * r_) {
    flag = true;
  } else {
    Vector v3(sv.p1_, o_);
    Vector v4(sv.p2_, o_);
    Vector v5(sv.p1_, sv.p2_);
    Vector v6(sv.p2_, sv.p1_);
    double res;
    if (ScalarPr(v3, v5) >= 0 && ScalarPr(v4, v6) >= 0) {
      Vector v1(sv.p2_, o_);
      Vector v2(sv.p2_, sv.p1_);
      res = (1.0 * VectorPr(v1, v2)) / Mod(sv.p1_, sv.p2_);
      if (res <= (1.0 * r_) && Mod(o_, sv.p1_) >= r_ && Mod(o_, sv.p2_) >= r_) {
        flag = true;
      }
    } else {
      flag = false;
    }
  }
  return flag;
}

Circle *Circle::Clone() const {
  return (new Circle(o_, r_));
}

std::string Circle::ToString() const {
  std::string s;
  s = "Circle(Point(";
  s += DoString(o_.x);
  s += ", ";
  s += DoString(o_.y);
  s += "), ";
  s += DoString(r_);
  s += ")";
  return s;
}
}  // namespace geometry
