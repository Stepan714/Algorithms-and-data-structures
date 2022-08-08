#pragma once
#include <stdexcept>
#include <iostream>
#include <cstring>
class RationalDivisionByZero : public std::runtime_error {
 public:
  RationalDivisionByZero() : std::runtime_error("RationalDivisionByZero") {
  }
};

class Rational {
  int numerator_;
  int denominator_;
  int Gcd(int, int);
  void Constructor();

 public:
  Rational();
  Rational(int);  // NOLINT
  Rational(int, int);
  int GetNumerator() const;
  int GetDenominator() const;
  void SetNumerator(int);
  void SetDenominator(int);
  Rational operator+() const;
  Rational operator-() const;
  friend Rational operator+(const Rational&, const Rational&);
  friend Rational operator-(const Rational&, const Rational&);
  friend Rational operator/(const Rational&, const Rational&);
  friend Rational operator*(const Rational&, const Rational&);
  friend std::ostream& operator<<(std::ostream& out, const Rational&);
  friend std::istream& operator>>(std::istream& in, Rational&);
  Rational& operator+=(const Rational&);
  Rational& operator-=(const Rational&);
  Rational& operator/=(const Rational&);
  Rational& operator*=(const Rational&);
  friend bool operator<(const Rational&, const Rational&);
  friend bool operator<=(const Rational&, const Rational&);
  friend bool operator>(const Rational&, const Rational&);
  friend bool operator>=(const Rational&, const Rational&);
  friend bool operator==(const Rational&, const Rational&);
  friend bool operator!=(const Rational&, const Rational&);
  Rational& operator++();
  Rational operator++(int);
  Rational& operator--();
  Rational operator--(int);
};
