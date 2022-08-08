#include "../point.h"
#include "../vector.h"
#include "../segment.h"
#include "../ray.h"

namespace geometry {
Ray &Ray::Move(const Vector &rv) {
  o_.Move(rv);
  v_.p1_.Move(rv);
  v_.p2_.Move(rv);
  return *this;
}

bool Ray::ContainsPoint(const Point &p) const {
  Line len(v_.p1_, v_.p2_);
  Vector v1(len.p1_, p);
  Vector v2(p, len.p2_);
  Vector rv(o_, p);
  bool flag = false;
  if (VectorPr(v1, v2) == 0 && ScalarPr(rv, v_) >= 0) {
    flag = true;
  }
  return flag;
}

bool Ray::CrossesSegment(const Segment &sv) const {
  Line len1(sv.p1_, sv.p2_);
  bool flag = false;
  if (len1.CrossesSegment(sv)) {
    Line len2(v_.p1_, v_.p2_);
    int64_t a1 = len1.p1_.y - len1.p2_.y;
    int64_t a2 = len2.p1_.y - len2.p2_.y;
    int64_t b1 = len1.p2_.x - len1.p1_.x;
    int64_t b2 = len2.p2_.x - len2.p1_.x;
    int64_t c1 = -1 * a1 * len1.p1_.x - b1 * len1.p1_.y;
    int64_t c2 = -1 * a2 * len2.p1_.x - b2 * len2.p1_.y;
    if (a2 * b1 - b2 * a1 != 0) {
      double x1 = (b2 * c1 - b1 * c2) / (a2 * b1 - b2 * a1);
      if (v_.p1_.x < v_.p2_.x) {
        if (1.0 * v_.p1_.x <= x1) {
          flag = true;
        }
      } else {
        if (1.0 * v_.p1_.x >= x1) {
          flag = true;
        }
      }
    } else {
      if (v_.p1_.x <= v_.p2_.x && v_.p1_.y <= v_.p2_.y) {
        if (sv.p1_.x >= v_.p1_.x && sv.p1_.y >= v_.p1_.y) {
          flag = true;
        }
      }
      if (v_.p1_.x <= v_.p2_.x && v_.p1_.y <= v_.p2_.y) {
        if (sv.p2_.x >= v_.p1_.x && sv.p2_.y >= v_.p1_.y) {
          flag = true;
        }
      }
      if (v_.p1_.x <= v_.p2_.x && v_.p1_.y >= v_.p2_.y) {
        if (sv.p1_.x >= v_.p1_.x && sv.p1_.y <= v_.p1_.y) {
          flag = true;
        }
      }
      if (v_.p1_.x <= v_.p2_.x && v_.p1_.y >= v_.p2_.y) {
        if (sv.p2_.x >= v_.p1_.x && sv.p2_.y <= v_.p1_.y) {
          flag = true;
        }
      }
      if (v_.p1_.x >= v_.p2_.x && v_.p1_.y <= v_.p2_.y) {
        if (sv.p1_.x <= v_.p1_.x && sv.p1_.y >= v_.p1_.y) {
          flag = true;
        }
      }
      if (v_.p1_.x >= v_.p2_.x && v_.p1_.y <= v_.p2_.y) {
        if (sv.p2_.x <= v_.p1_.x && sv.p2_.y >= v_.p1_.y) {
          flag = true;
        }
      }
      if (v_.p1_.x <= v_.p2_.x && v_.p1_.y >= v_.p2_.y) {
        if (sv.p1_.x <= v_.p1_.x && sv.p1_.y <= v_.p1_.y) {
          flag = true;
        }
      }
      if (v_.p1_.x <= v_.p2_.x && v_.p1_.y >= v_.p2_.y) {
        if (sv.p2_.x <= v_.p1_.x && sv.p2_.y <= v_.p1_.y) {
          flag = true;
        }
      }
    }
  }
  return flag;
}

Ray *Ray::Clone() const {
  return (new Ray(o_, v_));
}

std::string Ray::ToString() const {
  std::string s;
  s = "Ray(Point(";
  s += DoString(o_.x);
  s += ", ";
  s += DoString(o_.y);
  s += "), Vector(";
  s += DoString(v_.p2_.x - v_.p1_.x);
  s += ", ";
  s += DoString(v_.p2_.y - v_.p1_.y);
  s += "))";
  return s;
}
}  // namespace geometry
