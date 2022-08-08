#include "../point.h"
#include "../vector.h"
#include "../segment.h"
#include "../line.h"

namespace geometry {
Line::Line(const Point &p1, const Point &p2) {
  p1_ = p1;
  p2_ = p2;
  v_.p1_ = p1;
  v_.p2_ = p2;
}
Line::Line(const Segment &sv) {
  p1_ = sv.p1_;
  p2_ = sv.p2_;
  v_.p1_ = p1_;
  v_.p2_ = p2_;
}
Line &Line::Move(const Vector &rv) {
  p1_.Move(rv);
  p2_.Move(rv);
  v_.p2_.Move(rv);
  v_.p1_.Move(rv);
  return *this;
}

bool Line::ContainsPoint(const Point &p) const {
  bool flag = false;
  Vector v1(p1_, p);
  Vector v2(p, p2_);
  if (VectorPr(v1, v2) == 0) {
    flag = true;
  }
  return flag;
}

bool Line::CrossesSegment(const Segment &sv) const {
  int64_t c = -1 * ((p2_.y - p1_.y) * p2_.x + p2_.y * (p1_.x - p2_.x));
  int64_t a = p2_.y - p1_.y;
  int64_t b = p1_.x - p2_.x;
  int64_t res1 = a * sv.p1_.x + b * sv.p1_.y + c;
  int64_t res2 = a * sv.p2_.x + b * sv.p2_.y + c;
  bool flag = false;
  if (res1 * res2 <= 0) {
    flag = true;
  }
  return flag;
}

Line *Line::Clone() const {
  return (new Line(p1_, p2_));
}

std::string Line::ToString() const {
  int64_t c = -1 * ((p2_.y - p1_.y) * p2_.x + p2_.y * (p1_.x - p2_.x));
  int64_t a = p2_.y - p1_.y;
  int64_t b = p1_.x - p2_.x;
  std::string s;
  s = "Line(";
  s += DoString(a);
  s += ", ";
  s += DoString(b);
  s += ", ";
  s += DoString(c);
  s += ")";
  return s;
}
}  // namespace geometry
