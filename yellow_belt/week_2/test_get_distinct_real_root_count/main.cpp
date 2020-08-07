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

int GetDistinctRealRootCount(double a, double b, double c);

string GetPartOfHint(double value, char x) {
  stringstream part;
  char sign;
  if (value > 0) {
    sign = '>';
  } else if (value < 0) {
    sign = '<';
  } else {
    sign = '=';
  }
  part << "| " << x << ' ' << sign << " 0 |";
  return part.str();
}

string GetHint(double a, double b, double c) {
  stringstream hint;
  hint << GetPartOfHint(a, 'a') << GetPartOfHint(b, 'b') << GetPartOfHint(c, 'c');
  return hint.str();
}

void TestDiscriminantGreatZero() {
  double a, b, c;
  int expected = 2;
  {
    a = 1.0;
    b = 4.0;
    c = 1.0;
    AssertEqual(GetDistinctRealRootCount(a, b, c), expected, GetHint(a, b, c));
  }
  {
    a = -1.0;
    b = 4.0;
    c = 1.0;
    AssertEqual(GetDistinctRealRootCount(a, b, c), expected, GetHint(a, b, c));
  }
  {
    a = -1.0;
    b = 4.0;
    c = -1.0;
    AssertEqual(GetDistinctRealRootCount(a, b, c), expected, GetHint(a, b, c));
  }
  {
    a = 1.0;
    b = 4.0;
    c = -1.0;
    AssertEqual(GetDistinctRealRootCount(a, b, c), expected, GetHint(a, b, c));
  }
  {
    a = 1.0;
    b = -4.0;
    c = 1.0;
    AssertEqual(GetDistinctRealRootCount(a, b, c), expected, GetHint(a, b, c));
  }
}

void TestDiscriminantLessZero() {
  double a, b, c;
  int expected = 0;
  string addition = "D < 0";
  {
    a = 1.0;
    b = 1.0;
    c = 1.0;
    AssertEqual(GetDistinctRealRootCount(a, b, c), expected, GetHint(a, b, c));
  }
  {
    a = -1.0;
    b = 1.0;
    c = -1.0;
    AssertEqual(GetDistinctRealRootCount(a, b, c), expected, GetHint(a, b, c));
  }
  {
    a = 1.0;
    b = -1.0;
    c = 1.0;
    AssertEqual(GetDistinctRealRootCount(a, b, c), expected, GetHint(a, b, c));
  }
}

void TestDiscriminantEqualZero() {
  double a, b, c;
  int expected = 1;
  string addition = "D = 0";
  {
    a = 1.0;
    b = 2.0;
    c = 1.0;
    AssertEqual(GetDistinctRealRootCount(a, b, c), expected, GetHint(a, b, c));
  }
  {
    a = -1.0;
    b = 2.0;
    c = -1.0;
    AssertEqual(GetDistinctRealRootCount(a, b, c), expected, GetHint(a, b, c));
  }
  {
    a = 1.0;
    AssertEqual(GetDistinctRealRootCount(a, 0.0, 0.0), expected, GetHint(a, 0, 0));
  }
  {
    a = 1.0;
    b = -2.0;
    c = 1.0;
    AssertEqual(GetDistinctRealRootCount(a, b, c), expected, GetHint(a, b, c));
  }
  {
    a = -1.0;
    b = -2.0;
    c = -1.0;
    AssertEqual(GetDistinctRealRootCount(a, b, c), expected, GetHint(a, b, c));
  }
}

void TestLinearEquation() {
  double b, c;
  int expected;
  {
    expected = 1;
    {
      b = 4.0;
      c = 2.0;
      AssertEqual(GetDistinctRealRootCount(0, b, c), expected, GetHint(0, b, c));
    }
    {
      b = 4.0;
      c = -2.0;
      AssertEqual(GetDistinctRealRootCount(0, b, c), expected, GetHint(0, b, c));
    }
    {
      b = -4.0;
      c = -2.0;
      AssertEqual(GetDistinctRealRootCount(0, b, c), expected, GetHint(0, b, c));
    }
    {
      b = -4.0;
      c = 2.0;
      AssertEqual(GetDistinctRealRootCount(0, b, c), expected, GetHint(0, b, c));
    }
  }
  {
    expected = 0;
    {
      c = 2.0;
      AssertEqual(GetDistinctRealRootCount(0, 0, c), expected, GetHint(0, 0, c));
    }
    {
      c = -2.0;
      AssertEqual(GetDistinctRealRootCount(0, 0, c), expected, GetHint(0, 0, c));
    }
  }
}

void TestAll() {
  TestRunner tr;
  tr.RunTest(TestDiscriminantEqualZero, "TestDiscriminantEqualZero");
  tr.RunTest(TestDiscriminantGreatZero, "TestDiscriminantGreatZero");
  tr.RunTest(TestDiscriminantLessZero, "TestDiscriminantLessZero");
  tr.RunTest(TestLinearEquation, "TestLinearEquation");
}

int main() {
  TestAll();
  return 0;
}
