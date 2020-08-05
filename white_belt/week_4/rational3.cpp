/*
#include <numeric>
#include <iostream>

class Rational {
public:
  Rational() {
    numerator_ = 0;
    denominator_ = 1;
  }
  Rational(int numerator, int denominator) {
    numerator_ = numerator;
    denominator_ = denominator;
    normalize();
  }

  int Numerator() const { return numerator_;}
  int Denominator() const { return denominator_;}

private:
  int numerator_;
  int denominator_;

  void normalize() {
    if (numerator_ * denominator_ > 0) {
      numerator_ = std::abs(numerator_);
      denominator_ = std::abs(denominator_);
    } else if (numerator_ * denominator_ < 0) {
      numerator_ = -std::abs(numerator_);
      denominator_ = std::abs(denominator_);
    } else {
      denominator_ = 1;
    }
    int gcd = std::gcd(numerator_, denominator_);
    numerator_ = numerator_ / gcd;
    denominator_ = denominator_ / gcd;
  }
};


bool operator==(const Rational& lhs, const Rational& rhs) {
  return (lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator());
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
  if (lhs.Denominator() == rhs.Denominator()) {
    return {lhs.Numerator() + rhs.Numerator(), lhs.Denominator()};
  }
  return {lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator(),
          lhs.Denominator() * rhs.Denominator()};
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
  if (lhs.Denominator() == rhs.Denominator()) {
    return {lhs.Numerator() - rhs.Numerator(), lhs.Denominator()};
  }
  return {lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator(),
          lhs.Denominator() * rhs.Denominator()};
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
  return {lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator()};
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
  int gcd1 = std::gcd(lhs.Numerator(), rhs.Numerator());
  int gcd2 = std::gcd(lhs.Denominator(), rhs.Denominator());
  return Rational{(lhs.Numerator() / gcd1) * (rhs.Denominator() / gcd2),
                  (lhs.Denominator() / gcd2) * (rhs.Numerator() / gcd1)};
}


int main() {
  using namespace std;

  {
    Rational a(2, 3);
    Rational b(4, 3);
    Rational c = a * b;
    bool equal = c == Rational(8, 9);
    if (!equal) {
      cout << "2/3 * 4/3 != 8/9" << endl;
      return 1;
    }
  }

  {
    Rational a(5, 4);
    Rational b(15, 8);
    Rational c = a / b;
    bool equal = c == Rational(2, 3);
    if (!equal) {
      cout << "5/4 / 15/8 != 2/3" << endl;
      return 2;
    }
  }

  Rational a(2140000000, 2140000001);
  Rational b(2140000000, 2140000001);
  Rational c = a / b;
  cout << c.Numerator() << '/' << c.Denominator() << '\n';

  cout << "OK" << endl;
  return 0;
}
*/
