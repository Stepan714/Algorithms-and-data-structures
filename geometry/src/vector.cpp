#include "../point.h"
#include "../vector.h"
#include "../segment.h"

namespace geometry {

int64_t VectorPr(const Vector &v1, const Vector &v2) {
  int64_t res = (v1.p2_.x - v1.p1_.x) * (v2.p2_.y - v2.p1_.y);
  res -= (v1.p2_.y - v1.p1_.y) * (v2.p2_.x - v2.p1_.x);
  return res;
}
int64_t ScalarPr(const Vector &v1, const Vector &v2) {
  int64_t res = ((v1.p2_.x - v1.p1_.x) * (v2.p2_.x - v2.p1_.x) + (v1.p2_.y - v1.p1_.y) * (v2.p2_.y - v2.p1_.y));
  return res;
}

double Mod(const Point &a, const Point &b) {
  double c = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
  return c;
}
}  // namespace geometry
