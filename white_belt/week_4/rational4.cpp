/*
#include <numeric>
#include <iostream>
#include <sstream>

class Rational {
public:
  Rational() {
    numerator_ = 0;
    denominator_ = 1;
  }
  Rational(int numerator, int denominator) {
    numerator_ = numerator;
    denominator_ = denominator;
    update();
  }

  int Numerator() const { return numerator_;}
  int Denominator() const { return denominator_;}

  void setNumerator(int value) {
    numerator_ = value;
    update();
  }
  void setDenominator(int value) {
    denominator_ = value;
    update();
  }

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
  return {lhs.Numerator() * rhs.Denominator(), lhs.Denominator() * rhs.Numerator()};
}

std::istream& operator>>(std::istream& in, Rational& r) {
  int numerator = r.Numerator();
  int denominator = r.Denominator();
  in >> numerator;
  in.ignore(1);
  in >> denominator;
  r = {numerator, denominator};
  return in;
}

std::ostream& operator<<(std::ostream& out, const Rational& r) {
  out << r.Numerator() << '/' << r.Denominator();
  return out;
}


int main() {
  using namespace std;

  {
    ostringstream output;
    output << Rational(-6, 8);
    if (output.str() != "-3/4") {
      cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
      return 1;
    }
  }

  {
    istringstream input("5/7");
    Rational r;
    input >> r;
    bool equal = r == Rational(5, 7);
    if (!equal) {
      cout << "5/7 is incorrectly read as " << r << endl;
      return 2;
    }
  }

  {
    istringstream input("5/7 10/8");
    Rational r1, r2;
    input >> r1 >> r2;
    bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
    if (!correct) {
      cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
      return 3;
    }

    input >> r1;
    input >> r2;
    correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
    if (!correct) {
      cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
      return 4;
    }
  }


  cout << "OK" << endl;
  return 0;
}
*/
