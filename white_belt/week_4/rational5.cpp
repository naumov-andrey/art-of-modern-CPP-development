/*
#include <numeric>
#include <iostream>
#include <map>
#include <set>
#include <vector>

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

bool operator<(const Rational& lhs, const Rational& rhs) {
  return (lhs.Numerator() * rhs.Denominator() < rhs.Numerator() * lhs.Denominator());
}


int main() {
  using namespace std;

  {
    const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
    if (rs.size() != 3) {
      cout << "Wrong amount of items in the set" << endl;
      return 1;
    }

    vector<Rational> v;
    for (auto x : rs) {
      v.push_back(x);
    }
    if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
      cout << "Rationals comparison works incorrectly" << endl;
      return 2;
    }
  }

  {
    map<Rational, int> count;
    ++count[{1, 2}];
    ++count[{1, 2}];

    ++count[{2, 3}];

    if (count.size() != 2) {
      cout << "Wrong amount of items in the map" << endl;
      return 3;
    }
  }

  cout << "OK" << endl;
  return 0;
}
*/
