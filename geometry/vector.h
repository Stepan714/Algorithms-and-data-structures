#include "point.h"

#pragma once
namespace geometry {
class Vector {
 public:
  Point p1_;
  Point p2_;
  Vector() : p1_(), p2_() {
  }
  Vector(const Point& p1, const Point& p2) {
    p1_ = p1;
    p2_ = p2;
  }
  Vector(const Vector& v) = default;
  friend Vector operator+(const Vector& v1, const Vector& v2) {
    Vector c;
    c.p1_.x = v1.p1_.x + v2.p1_.x;
    c.p1_.y = v1.p1_.y + v2.p1_.y;
    c.p2_.x = v1.p2_.x + v2.p2_.x;
    c.p2_.y = v1.p2_.y + v2.p2_.y;
    return c;
  }
  friend Vector operator-(const Vector& v1, const Vector& v2) {
    Vector c;
    c.p1_.x = v1.p1_.x - v2.p1_.x;
    c.p1_.y = v1.p1_.y - v2.p1_.y;
    c.p2_.x = v1.p2_.x - v2.p2_.x;
    c.p2_.y = v1.p2_.y - v2.p2_.y;
    return c;
  }
  Vector& operator+(Vector& v) {
    return v;
  }
  Vector& operator-(Vector& v) {
    v.p1_.x *= -1;
    v.p1_.y *= -1;
    v.p2_.x *= -1;
    v.p2_.y *= -1;
    return v;
  }
  Vector& operator+=(const Vector& v) {
    p1_.x += v.p1_.x;
    p1_.y += v.p1_.y;
    p2_.x += v.p2_.x;
    p2_.y += v.p2_.y;
    return *this;
  }
  Vector& operator-=(const Vector& v) {
    p1_.x -= v.p1_.x;
    p1_.y -= v.p1_.y;
    p2_.x -= v.p2_.x;
    p2_.y -= v.p2_.y;
    return *this;
  }
  friend Vector& operator*(Vector& v, int64_t n) {
    v.p1_.x *= n;
    v.p1_.y *= n;
    v.p2_.x *= n;
    v.p2_.y *= n;
    return v;
  }
  friend Vector& operator/(Vector& v, int64_t n) {
    v.p1_.x /= n;
    v.p1_.y /= n;
    v.p2_.x /= n;
    v.p2_.y /= n;
    return v;
  }
  Vector& operator/=(int64_t n) {
    p1_.x /= n;
    p1_.y /= n;
    p2_.x /= n;
    p2_.y /= n;
    return *this;
  }
  Vector& operator*=(int64_t n) {
    p1_.x *= n;
    p1_.y *= n;
    p2_.x *= n;
    p2_.y *= n;
    return *this;
  }
  friend bool operator==(const Vector& v1, const Vector& v2) {
    bool flag = false;
    if (v2.p2_.x - v2.p1_.x == v1.p2_.x - v1.p1_.x && v2.p2_.y - v2.p1_.y == v1.p2_.y - v1.p1_.y) {
      flag = true;
    }
    return flag;
  }
};
int64_t VectorPr(const Vector& v1, const Vector& v2);
int64_t ScalarPr(const Vector& v1, const Vector& v2);
double Mod(const Point& a, const Point& b);
}  // namespace geometry
