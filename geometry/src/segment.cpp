#include "../point.h"
#include "../vector.h"
#include "../segment.h"

namespace geometry {
Segment &Segment::Move(const Vector &v) {
  p1_ = p1_.Move(v);
  p2_ = p2_.Move(v);
  return *this;
}

bool Segment::ContainsPoint(const Point &p) const {
  bool flag = false;
  Vector v1(p1_, p);
  Vector v2(p, p2_);
  int64_t x_min = p1_.x > p2_.x ? p2_.x : p1_.x;
  int64_t x_max = p1_.x < p2_.x ? p2_.x : p1_.x;
  int64_t y_min = p1_.y > p2_.y ? p2_.y : p1_.y;
  int64_t y_max = p1_.y < p2_.y ? p2_.y : p1_.y;
  if (VectorPr(v1, v2) == 0 && p.x >= x_min && p.x <= x_max && p.y >= y_min && p.y <= y_max) {
    flag = true;
  }
  return flag;
}

Segment *Segment::Clone() const {
  return (new Segment(p1_, p2_));
}

std::string Segment::ToString() const {
  std::string s;
  s = "Segment(";
  s += p1_.ToString();
  s += ", ";
  s += p2_.ToString();
  s += ")";
  return s;
}

void Build(Vector &v1, Vector &v2, const Segment &d, const Segment &e) {
  v1.p1_.x = d.p1_.x;
  v1.p1_.y = d.p1_.y;
  v1.p2_.x = d.p2_.x;
  v1.p2_.y = d.p2_.y;
  v2.p1_.x = e.p1_.x;
  v2.p1_.y = e.p1_.y;
  v2.p2_.x = e.p2_.x;
  v2.p2_.y = e.p2_.y;
}

bool Ans(const Segment &d, const Segment &e) {
  Vector v1, v2;
  Build(v1, v2, d, e);
  int score = 0;
  int64_t c1 = -1 * ((d.p2_.y - d.p1_.y) * d.p2_.x + d.p2_.y * (d.p1_.x - d.p2_.x));
  int64_t a1 = d.p2_.y - d.p1_.y;
  int64_t b1 = d.p1_.x - d.p2_.x;
  int64_t c2 = -1 * ((e.p2_.y - e.p1_.y) * e.p2_.x + e.p2_.y * (e.p1_.x - e.p2_.x));
  int64_t a2 = e.p2_.y - e.p1_.y;
  int64_t b2 = e.p1_.x - e.p2_.x;
  if ((a1 * e.p1_.x + b1 * e.p1_.y + c1) * (a1 * e.p2_.x + b1 * e.p2_.y + c1) <= 0) {
    score++;
  }
  if ((a2 * d.p1_.x + b2 * d.p1_.y + c2) * (a2 * d.p2_.x + b2 * d.p2_.y + c2) <= 0) {
    score++;
  }
  auto min1_x = v1.p1_.x < v1.p2_.x ? v1.p1_.x : v1.p2_.x;
  auto min2_x = v2.p1_.x < v2.p2_.x ? v2.p1_.x : v2.p2_.x;
  auto min1_y = v1.p1_.y < v1.p2_.y ? v1.p1_.y : v1.p2_.y;
  auto min2_y = v2.p1_.y < v2.p2_.y ? v2.p1_.y : v2.p2_.y;
  auto max1_x = v1.p1_.x > v1.p2_.x ? v1.p1_.x : v1.p2_.x;
  auto max2_x = v2.p1_.x > v2.p2_.x ? v2.p1_.x : v2.p2_.x;
  auto max1_y = v1.p1_.y > v1.p2_.y ? v1.p1_.y : v1.p2_.y;
  auto max2_y = v2.p1_.y > v2.p2_.y ? v2.p1_.y : v2.p2_.y;
  if ((min1_x >= min2_x && min1_x <= max2_x) || (min2_x >= min1_x && min2_x <= max1_x)) {
    score++;
  }
  if ((min1_y >= min2_y && min1_y <= max2_y) || (min2_y >= min1_y && min2_y <= max1_y)) {
    score++;
  }
  bool flag = true;
  if (score != 4) {
    flag = false;
  }
  return flag;
}

bool Segment::CrossesSegment(const Segment &s) const {
  bool flag = Ans(*this, s);
  bool tmp = false;
  if (flag) {
    tmp = true;
  }
  return tmp;
}
}  // namespace geometry
