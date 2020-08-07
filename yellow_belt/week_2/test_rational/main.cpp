#include <sstream>
#include <exception>
#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u,
                 const string& hint)
{
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u
       << " hint: " << hint;
    throw runtime_error(os.str());
  }
}

inline void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (runtime_error& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};


void TestDefaultCtor() {
  Rational r;
  AssertEqual(r.Numerator(), 0, "Default numerator");
  AssertEqual(r.Denominator(), 1, "Default denominator");
}

void TestCtor() {
  {
    Rational r(2, 1);
    AssertEqual(r.Numerator(), 2, "Simple ctor numerator");
    AssertEqual(r.Denominator(), 1, "Simple ctor denominator");
  }
  {
    Rational r(4, 2);
    AssertEqual(r.Numerator(), 2, "Ctor with reduction numerator");
    AssertEqual(r.Denominator(), 1, "Ctor with reduction denominator");
  }
  {
    Rational r(100000, 100000);
    AssertEqual(r.Numerator(), 1, "Ctor with full reduction numerator");
    AssertEqual(r.Denominator(), 1, "Ctor with full reduction denominator");
  }
}

void TestNegativity() {
  {
    Rational r(-2, 1);
    AssertEqual(r.Numerator(), -2, "Simple negativity numerator");
    AssertEqual(r.Denominator(), 1, "Simple negativity denominator");
  }
  {
    Rational r(2, -1);
    AssertEqual(r.Numerator(), -2, "Negativity with moving sign numerator");
    AssertEqual(r.Denominator(), 1, "Negativity with moving sign denominator");
  }
}

void TestPositivity() {
  Rational r(-2, -1);
  AssertEqual(r.Numerator(), 2, "Positivity numerator");
  AssertEqual(r.Denominator(), 1, "Positivity denominator");
}

void TestZeroRational() {
  {
    Rational r(0, 1);
    AssertEqual(r.Numerator(), 0, "Simple zero rational's numerator");
    AssertEqual(r.Denominator(), 1, "Simple zero rational's denominator");
  }
  {
    Rational r(0, -2);
    AssertEqual(r.Numerator(), 0, "Zero rational's numerator");
    AssertEqual(r.Denominator(), 1, "Zero rational's denominator");
  }
  {
    Rational r(0, 2);
    AssertEqual(r.Numerator(), 0, "Zero rational's numerator");
    AssertEqual(r.Denominator(), 1, "Zero rational's denominator");
  }
}

void TestAll() {
  TestRunner tr;
  tr.RunTest(TestDefaultCtor, "TestDefaultCtor");
  tr.RunTest(TestCtor, "TestCtor");
  tr.RunTest(TestNegativity, "TestNegativity");
  tr.RunTest(TestPositivity, "TestPositivity");
  tr.RunTest(TestZeroRational, "TestZeroRational");
}

int main() {
  TestAll();
  return 0;
}
