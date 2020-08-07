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

void TestChangeFirstName() {
  {
    Person p;
    p.ChangeFirstName(0, "A");
    AssertEqual(p.GetFullName(0), "A with unknown last name", "First change of name");
  }
  {
    Person p;
    p.ChangeFirstName(0, "A");
    p.ChangeFirstName(0, "B");
    AssertEqual(p.GetFullName(0), "B with unknown last name", "Second change of name");
  }
  {
    Person p;
    p.ChangeFirstName(0, "A");
    p.ChangeFirstName(1, "B");
    AssertEqual(p.GetFullName(0), "A with unknown last name", "First change of name without overlapping");
    AssertEqual(p.GetFullName(1), "B with unknown last name", "Second change of name without overlapping");
  }
}

void TestChangeLastName() {
  {
    Person p;
    p.ChangeLastName(0, "A");
    AssertEqual(p.GetFullName(0), "A with unknown first name", "First change of name");
  }
  {
    Person p;
    p.ChangeLastName(0, "A");
    p.ChangeLastName(0, "B");
    AssertEqual(p.GetFullName(0), "B with unknown first name", "Second change of name");
  }
  {
    Person p;
    p.ChangeLastName(0, "A");
    p.ChangeLastName(1, "B");
    AssertEqual(p.GetFullName(0), "A with unknown first name", "First change of name without overlapping");
    AssertEqual(p.GetFullName(1), "B with unknown first name", "Second change of name without overlapping");
  }
}

void TestGetFullName() {
  {
    Person p;
    AssertEqual(p.GetFullName(0), "Incognito", "No name");
  }
  {
    Person p;
    p.ChangeFirstName(0, "A");
    AssertEqual(p.GetFullName(0), "A with unknown last name", "First name without last");
  }
  {
    Person p;
    p.ChangeLastName(0, "A");
    AssertEqual(p.GetFullName(0), "A with unknown first name", "Last name without first");
  }
  {
    Person p;
    p.ChangeFirstName(0, "A");
    p.ChangeLastName(0, "B");
    AssertEqual(p.GetFullName(0), "A B", "First and last name");
  }
}

void TestAll() {
  TestRunner tr;
  tr.RunTest(TestChangeFirstName, "TestChangeFirstName");
  tr.RunTest(TestChangeLastName, "TestChangeLastName");
  tr.RunTest(TestGetFullName, "TestGetFullName");
}

int main() {
  TestAll();
  return 0;
}
