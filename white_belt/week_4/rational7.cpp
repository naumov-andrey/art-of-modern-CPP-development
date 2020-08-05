/*
#include <numeric>
#include <iostream>
#include <set>
#include <exception>
#include <stdexcept>


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
  if (rhs.Numerator() == 0) {
    throw std::domain_error("zero division");
  }
  int gcd1 = std::gcd(lhs.Numerator(), rhs.Numerator());
  int gcd2 = std::gcd(lhs.Denominator(), rhs.Denominator());
  return Rational{(lhs.Numerator() / gcd1) * (rhs.Denominator() / gcd2),
                  (lhs.Denominator() / gcd2) * (rhs.Numerator() / gcd1)};
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

bool operator<(const Rational& lhs, const Rational& rhs) {
  return (lhs.Numerator() * rhs.Denominator() < rhs.Numerator() * lhs.Denominator());
}


int main() {
  Rational a, b;
  char operation;
  try {
    std::cin >> a >> operation >> b;
    if (operation == '+') {
      std::cout << a + b;
    } else if (operation == '-') {
      std::cout << a - b;
    } else if (operation == '*') {
      std::cout << a * b;
    } else if (operation == '/') {
      std::cout << a / b;
    }
  } catch (std::invalid_argument& ex) {
    std::cout << "Invalid argument";
  } catch (std::domain_error& ex) {
    std::cout << "Division by zero";
  }
  return 0;
}
*/
