#include <iostream>
#include <map>
#include <string>

using namespace std;

string GetName(const map<int ,string>& name_for_year, int year) {
  if (name_for_year.empty()) {
    return "";
  }
  auto lower_bound = name_for_year.upper_bound(year);
  if (lower_bound == name_for_year.begin()) {
    return lower_bound->first > year ? "" : lower_bound->second;
  }
  return prev(lower_bound)->second;
}

class Person {
public:
  void ChangeFirstName(int year, const string& first_name) {
    first_name_for_year_[year] = first_name;
  }

  void ChangeLastName(int year, const string& last_name) {
    last_name_for_year_[year] = last_name;
  }

  string GetFullName(int year) {
    string first_name = GetName(first_name_for_year_, year);
    string last_name = GetName(last_name_for_year_, year);
    if (first_name.empty() && last_name.empty()) {
      return "Incognito";
    }
    if (first_name.empty()) {
      return last_name + " with unknown first name";
    }
    if (last_name.empty()) {
      return first_name + " with unknown last name";
    }
    return first_name + ' ' + last_name;
  }
private:
  map<int, string> first_name_for_year_, last_name_for_year_;
};

int main() {
  Person person;

  person.ChangeFirstName(1965, "Polina");
  person.ChangeLastName(1967, "Sergeeva");
  for (int year : {1900, 1965, 1990}) {
    cout << person.GetFullName(year) << endl;
  }

  person.ChangeFirstName(1970, "Appolinaria");
  for (int year : {1969, 1970}) {
    cout << person.GetFullName(year) << endl;
  }

  person.ChangeLastName(1968, "Volkova");
  for (int year : {1969, 1970}) {
    cout << person.GetFullName(year) << endl;
  }

  return 0;
}
