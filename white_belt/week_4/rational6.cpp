/*
#include <numeric>
#include <exception>
#include <set>

class Rational {
public:
  Rational() {
    numerator_ = 0;
    denominator_ = 1;
  }
  Rational(int numerator, int denominator) {
    if (denominator == 0) {
      throw std::invalid_argument("zero division");
    }
    numerator_ = numerator;
    denominator_ = denominator;
    update();
  }

  int Numerator() const { return numerator_;}
  int Denominator() const { return denominator_;}

private:
  int numerator_;
  int denominator_;

  void update() {
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
    if (gcd != 1) {
      numerator_ = numerator_ / gcd;
      denominator_ = denominator_ / gcd;
    }
  }
};


Rational operator/(const Rational& lhs, const Rational& rhs) {
  if (rhs.Numerator() == 0) {
    throw std::domain_error("zero division");
  }
  int gcd1 = std::gcd(lhs.Numerator(), rhs.Numerator());
  int gcd2 = std::gcd(lhs.Denominator(), rhs.Denominator());
  return Rational{(lhs.Numerator() / gcd1) * (rhs.Denominator() / gcd2),
                  (lhs.Denominator() / gcd2) * (rhs.Numerator() / gcd1)};
}

#include <iostream>
using namespace std;

int main() {
  try {
    Rational r(1, 0);
    cout << "Doesn't throw in case of zero denominator" << endl;
    return 1;
  } catch (invalid_argument&) {
  }

  try {
    auto x = Rational(1, 2) / Rational(0, 1);
    cout << "Doesn't throw in case of division by zero" << endl;
    return 2;
  } catch (domain_error&) {
  }

  cout << "OK" << endl;
  return 0;
}
*/
