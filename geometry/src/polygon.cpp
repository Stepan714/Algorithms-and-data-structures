#include "../point.h"
#include "../vector.h"
#include "../polygon.h"
#include "../segment.h"
namespace geometry {
Polygon &Polygon::Move(const Vector &rv) {
  for (size_t i = 0; i < mas_.size(); ++i) {
    mas_[i].Move(rv);
  }
  return *this;
}

Polygon *Polygon::Clone() const {
  return (new Polygon(mas_));
}

std::string Polygon::ToString() const {
  std::string s;
  s = "Polygon(";
  for (size_t i = 0; i < mas_.size(); ++i) {
    if (i != mas_.size() - 1) {
      s += "Point(";
      s += DoString(mas_[i].x);
      s += ", ";
      s += DoString(mas_[i].y);
      s += "), ";
    } else {
      s += "Point(";
      s += DoString(mas_[i].x);
      s += ", ";
      s += DoString(mas_[i].y);
      s += ")";
    }
  }
  s += ")";
  return s;
}

void Buildd(Vector &v1, Vector &v2, const Segment &d, const Segment &e) {
  v1.p1_.x = d.p1_.x;
  v1.p1_.y = d.p1_.y;
  v1.p2_.x = d.p2_.x;
  v1.p2_.y = d.p2_.y;
  v2.p1_.x = e.p1_.x;
  v2.p1_.y = e.p1_.y;
  v2.p2_.x = e.p2_.x;
  v2.p2_.y = e.p2_.y;
}

bool Anv(const Segment &d, const Segment &e) {
  Vector v1, v2;
  Buildd(v1, v2, d, e);
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

bool PolygF(const Polygon &p, const Point &c) {
  bool flag = false;
  for (size_t i = 0; i < p.mas_.size(); ++i) {
    if (p.mas_[i].x == c.x && p.mas_[i].y == c.y) {
      flag = true;
      break;
    }
  }
  Vector v1, v2;
  v1.p1_.x = c.x;
  v1.p1_.y = c.y;
  for (size_t i = 0; i < p.mas_.size() - 1; ++i) {
    v1.p2_.x = p.mas_[i].x;
    v1.p2_.y = p.mas_[i].y;
    v2.p1_.x = p.mas_[i].x;
    v2.p1_.y = p.mas_[i].y;
    v2.p2_.x = p.mas_[i + 1].x;
    v2.p2_.y = p.mas_[i + 1].y;
    if (VectorPr(v1, v2) == 0) {
      flag = true;
      break;
    }
  }
  if (flag) {
    return true;
  } else {
    int score = 0;
    Segment d, e;
    d.p1_.x = c.x;
    d.p1_.y = c.y;
    d.p2_.y = c.y;
    d.p2_.x = 10002;
    for (size_t i = 0; i < p.mas_.size() - 1; ++i) {
      e.p1_.x = p.mas_[i].x;
      e.p1_.y = p.mas_[i].y;
      e.p2_.x = p.mas_[i + 1].x;
      e.p2_.y = p.mas_[i + 1].y;
      if (Anv(d, e)) {
        score++;
      }
    }
    e.p1_.x = p.mas_[p.mas_.size() - 1].x;
    e.p1_.y = p.mas_[p.mas_.size() - 1].y;
    e.p2_.x = p.mas_[0].x;
    e.p2_.y = p.mas_[0].y;
    if (Anv(d, e)) {
      score++;
    }
    bool buf = false;
    if (score % 2 == 1) {
      buf = true;
    }
    return buf;
  }
}

bool Polygon::CrossesSegment(const Segment &s) const {
  bool flag = false;
  for (size_t i = 0; i < mas_.size() - 1; ++i) {
    Segment t(mas_[i], mas_[i + 1]);
    if (Anv(s, t)) {
      flag = true;
    }
  }
  Segment t(mas_[mas_.size() - 1], mas_[0]);
  if (Anv(s, t) && !flag) {
    flag = false;
  }
  return flag;
}

bool Polygon::ContainsPoint(const Point &p) const {
  bool flag = false;
  if (PolygF(*this, p)) {
    flag = true;
  }
  return flag;
}
}  // namespace geometry
