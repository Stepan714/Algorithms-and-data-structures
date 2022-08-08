#include "rational.h"
void Rational::Constructor() {
  int denominator_1 = this->denominator_;
  int numerator_1 = this->numerator_;
  if (denominator_1 == 0) {
    throw RationalDivisionByZero{};
  }
  int gcd = Gcd(numerator_1, denominator_1);
  if (denominator_1 > 0) {
    this->numerator_ = numerator_1 / gcd;
    this->denominator_ = denominator_1 / gcd;
  } else if (denominator_1 < 0) {
    this->numerator_ = (-1 * numerator_1) / gcd;
    this->denominator_ = (-1 * denominator_1) / gcd;
  }
}
Rational::Rational() {
  this->numerator_ = 0;
  this->denominator_ = 1;
}
Rational::Rational(int numerator_1) {  // NOLINT
  this->numerator_ = numerator_1;
  this->denominator_ = 1;
}
std::istream& operator>>(std::istream& in, Rational& frac) {
  frac.denominator_ = 1;
  int a, b;
  in >> a;
  if (in.peek() == '/') {
    char d;
    in >> d;
    in >> b;
    frac.numerator_ = a;
    frac.denominator_ = b;
  } else {
    frac.numerator_ = a;
  }
  frac.Constructor();
  return in;
}
Rational::Rational(int numerator_1, int denominator_1) {
  if (denominator_1 == 0) {
    throw RationalDivisionByZero{};
  }
  int gcd = Gcd(numerator_1, denominator_1);
  if (denominator_1 > 0) {
    this->numerator_ = numerator_1 / gcd;
    this->denominator_ = denominator_1 / gcd;
  } else if (denominator_1 < 0) {
    this->numerator_ = (-1 * numerator_1) / gcd;
    this->denominator_ = (-1 * denominator_1) / gcd;
  }
}
int Rational::Gcd(int value_1, int value_2) {
  int a = (0 <= value_1 ? value_1 : -1 * value_1);
  int b = (0 <= value_2 ? value_2 : -1 * value_2);
  while (a != 0 && b != 0) {
    if (a < b) {
      b %= a;
    } else {
      a %= b;
    }
  }
  return a + b;
}
int Rational::GetNumerator() const {
  return this->numerator_;
}
int Rational::GetDenominator() const {
  return this->denominator_;
}
void Rational::SetNumerator(int numerator_1) {
  this->numerator_ = numerator_1;
  this->Constructor();
}
void Rational::SetDenominator(int denominator_1) {
  this->denominator_ = denominator_1;
  this->Constructor();
}
Rational operator+(const Rational& frac_1, const Rational& frac_2) {
  Rational frac;
  frac.numerator_ = frac_1.numerator_ * frac_2.denominator_ + frac_2.numerator_ * frac_1.denominator_;
  frac.denominator_ = frac_1.denominator_ * frac_2.denominator_;
  frac.Constructor();
  return frac;
}
Rational operator-(const Rational& frac_1, const Rational& frac_2) {
  Rational frac;
  frac.numerator_ = frac_1.numerator_ * frac_2.denominator_ - frac_2.numerator_ * frac_1.denominator_;
  frac.denominator_ = frac_1.denominator_ * frac_2.denominator_;
  frac.Constructor();
  return frac;
}
Rational operator/(const Rational& frac_1, const Rational& frac_2) {
  Rational frac;
  frac.numerator_ = frac_1.numerator_ * frac_2.denominator_;
  frac.denominator_ = frac_1.denominator_ * frac_2.numerator_;
  if (frac.denominator_ == 0) {
    throw RationalDivisionByZero{};
  }
  frac.Constructor();
  return frac;
}
Rational operator*(const Rational& frac_1, const Rational& frac_2) {
  Rational frac;
  frac.numerator_ = frac_1.numerator_ * frac_2.numerator_;
  frac.denominator_ = frac_1.denominator_ * frac_2.denominator_;
  frac.Constructor();
  return frac;
}
std::ostream& operator<<(std::ostream& out, const Rational& frac) {
  if (frac.denominator_ == 0) {
    throw RationalDivisionByZero{};
  }
  if (frac.denominator_ != 1) {
    out << frac.numerator_ << "/" << frac.denominator_;
  } else {
    out << frac.numerator_;
  }
  return out;
}
Rational& Rational::operator+=(const Rational& frac) {
  numerator_ = numerator_ * frac.denominator_ + denominator_ * frac.numerator_;
  denominator_ = denominator_ * frac.denominator_;
  Constructor();
  return *this;
}
Rational& Rational::operator-=(const Rational& frac) {
  numerator_ = numerator_ * frac.denominator_ - denominator_ * frac.numerator_;
  denominator_ = denominator_ * frac.denominator_;
  Constructor();
  return *this;
}
Rational& Rational::operator/=(const Rational& frac) {
  numerator_ = numerator_ * frac.denominator_;
  denominator_ = denominator_ * frac.numerator_;
  Constructor();
  return *this;
}
Rational& Rational::operator*=(const Rational& frac) {
  numerator_ = numerator_ * frac.numerator_;
  denominator_ = denominator_ * frac.denominator_;
  Constructor();
  return *this;
}
bool operator<(const Rational& frac_1, const Rational& frac_2) {
  bool flag = false;
  auto tmp = frac_1.numerator_ * frac_2.denominator_ - frac_2.numerator_ * frac_1.denominator_;
  if (tmp < 0) {
    flag = true;
  }
  return flag;
}
bool operator<=(const Rational& frac_1, const Rational& frac_2) {
  bool flag = false;
  auto tmp = frac_1.numerator_ * frac_2.denominator_ - frac_2.numerator_ * frac_1.denominator_;
  if (tmp <= 0) {
    flag = true;
  }
  return flag;
}
bool operator>(const Rational& frac_1, const Rational& frac_2) {
  bool flag = false;
  auto tmp = frac_1.numerator_ * frac_2.denominator_ - frac_2.numerator_ * frac_1.denominator_;
  if (tmp > 0) {
    flag = true;
  }
  return flag;
}
bool operator>=(const Rational& frac_1, const Rational& frac_2) {
  bool flag = false;
  auto tmp = frac_1.numerator_ * frac_2.denominator_ - frac_2.numerator_ * frac_1.denominator_;
  if (tmp >= 0) {
    flag = true;
  }
  return flag;
}
bool operator==(const Rational& frac_1, const Rational& frac_2) {
  bool flag = false;
  auto tmp = frac_1.numerator_ * frac_2.denominator_ - frac_2.numerator_ * frac_1.denominator_;
  if (tmp == 0) {
    flag = true;
  }
  return flag;
}
bool operator!=(const Rational& frac_1, const Rational& frac_2) {
  bool flag = false;
  auto tmp = frac_1.numerator_ * frac_2.denominator_ - frac_2.numerator_ * frac_1.denominator_;
  if (tmp != 0) {
    flag = true;
  }
  return flag;
}
Rational Rational::operator+() const {
  Rational tmp;
  tmp.numerator_ = this->numerator_;
  tmp.denominator_ = this->denominator_;
  return tmp;
}
Rational Rational::operator-() const {
  Rational tmp;
  tmp.numerator_ = this->numerator_ * (-1);
  tmp.denominator_ = this->denominator_;
  return tmp;
}
Rational& Rational::operator++() {
  numerator_ += denominator_;
  Constructor();
  return *this;
}
Rational Rational::operator++(int) {
  Rational x;
  x.numerator_ = this->numerator_;
  x.denominator_ = this->denominator_;
  ++*this;
  Constructor();
  return x;
}
Rational& Rational::operator--() {
  this->numerator_ -= this->denominator_;
  Constructor();
  return *this;
}
Rational Rational::operator--(int) {
  Rational x;
  x.numerator_ = this->numerator_;
  x.denominator_ = this->denominator_;
  --*this;
  Constructor();
  return x;
}
