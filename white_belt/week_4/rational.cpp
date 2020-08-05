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


int main6() {
  using namespace std;

  {
    const Rational r(3, 10);
    if (r.Numerator() != 3 || r.Denominator() != 10) {
      cout << "Rational(3, 10) != 3/10" << endl;
      return 1;
    }
  }

  {
    const Rational r(8, 12);
    if (r.Numerator() != 2 || r.Denominator() != 3) {
      cout << "Rational(8, 12) != 2/3" << endl;
      return 2;
    }
  }

  {
    const Rational r(-4, 6);
    if (r.Numerator() != -2 || r.Denominator() != 3) {
      cout << "Rational(-4, 6) != -2/3" << endl;
      return 3;
    }
  }

  {
    const Rational r(4, -6);
    if (r.Numerator() != -2 || r.Denominator() != 3) {
      cout << "Rational(4, -6) != -2/3" << endl;
      return 3;
    }
  }

  {
    const Rational r(0, 15);
    if (r.Numerator() != 0 || r.Denominator() != 1) {
      cout << "Rational(0, 15) != 0/1" << endl;
      return 4;
    }
  }

  {
    const Rational defaultConstructed;
    if (defaultConstructed.Numerator() != 0 || defaultConstructed.Denominator() != 1) {
      cout << "Rational() != 0/1" << endl;
      return 5;
    }
  }

  cout << "OK" << endl;
  return 0;
}
*/
