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
    if (numerator * denominator > 0) {
      numerator = std::abs(numerator);
      denominator = std::abs(denominator);
    } else if (numerator * denominator < 0) {
      numerator = -std::abs(numerator);
      denominator = std::abs(denominator);
    } else {
      denominator = 1;
    }
    int gcd = std::gcd(numerator, denominator);
    if (gcd != 1) {
      numerator = numerator / gcd;
      denominator = denominator / gcd;
    }
    numerator_ = numerator;
    denominator_ = denominator;
  }

  int Numerator() const { return numerator_;}
  int Denominator() const { return denominator_;}

private:
  int numerator_;
  int denominator_;
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


int main7() {
  using namespace std;

  {
    Rational r1(4, 6);
    Rational r2(2, 3);
    bool equal = r1 == r2;
    if (!equal) {
      cout << "4/6 != 2/3" << endl;
      return 1;
    }
  }

  {
    Rational a(2, 3);
    Rational b(4, 3);
    Rational c = a + b;
    bool equal = c == Rational(2, 1);
    if (!equal) {
      cout << "2/3 + 4/3 != 2" << endl;
      return 2;
    }
  }

  {
    Rational a(5, 7);
    Rational b(2, 9);
    Rational c = a - b;
    bool equal = c == Rational(31, 63);
    if (!equal) {
      cout << "5/7 - 2/9 != 31/63" << endl;
      return 3;
    }
  }

  cout << "OK" << endl;
  return 0;
}
*/
