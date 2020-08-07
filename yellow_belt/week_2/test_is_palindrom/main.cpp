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


bool IsPalindrom(const string& s);


void TestEmptyStr() {
  AssertEqual(IsPalindrom(""), true, "Empty str");
}

void TestOneCharStr() {
  AssertEqual(IsPalindrom("a"), true, "One letter");
  AssertEqual(IsPalindrom(" "), true, "One ws");
  AssertEqual(IsPalindrom("1"), true, "One number");
  AssertEqual(IsPalindrom("$"), true, "One symbol");
}

void TestTwoCharStr() {
  AssertEqual(IsPalindrom("dd"), true, "Simple check");
  AssertEqual(IsPalindrom("md"), false, "Wrong str");
  AssertEqual(IsPalindrom("11"), true, "Str with numbers");
  AssertEqual(IsPalindrom("23"), false, "Str with different numbers");
  AssertEqual(IsPalindrom("%%"), true, "Str with symbols");
  AssertEqual(IsPalindrom("%$"), false, "Str with different symbols");
}

void TestManyCharStr() {
  AssertEqual(IsPalindrom("madam"), true, "Simple check");
  AssertEqual(IsPalindrom("madan"), false, "First and last letter mismatch");
  AssertEqual(IsPalindrom("madbam"), false, "Middle letters mismatch");
  AssertEqual(IsPalindrom("mad am"), false, "Ws in the middle");
  AssertEqual(IsPalindrom("     "), true, "5 ws str");
  AssertEqual(IsPalindrom("1a2d2a1"), true, "Str with numbers");
  AssertEqual(IsPalindrom("1ad2d2a1"), false, "Wrong str with numbers");
  AssertEqual(IsPalindrom("%a$a%"), true, "Str with symbols");
  AssertEqual(IsPalindrom("%ad$a%"), false, "Wrong str with symbols");
  AssertEqual(IsPalindrom("wasitacaroracatisaw"), true, "Long str");
  AssertEqual(IsPalindrom("wasitacatoracatisaw"), false, "Long wrong str");
}

void TestAll() {
  TestRunner tr;
  tr.RunTest(TestEmptyStr, "TestEmptyStr");
  tr.RunTest(TestOneCharStr, "TestOneCharStr");
  tr.RunTest(TestTwoCharStr, "TestTwoCharStr");
  tr.RunTest(TestManyCharStr, "TestManyCharStr");
}


int main() {
  TestAll();
  return 0;
}
