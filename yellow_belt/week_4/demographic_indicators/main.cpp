#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*enum class Gender {
  FEMALE,
  MALE
};

struct Person {
  int age;  // возраст
  Gender gender;  // пол
  bool is_employed;  // имеет ли работу
};

template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
  if (range_begin == range_end) {
    return 0;
  }
  vector<typename InputIt::value_type> range_copy(range_begin, range_end);
  auto middle = begin(range_copy) + range_copy.size() / 2;
  nth_element(
      begin(range_copy), middle, end(range_copy),
      [](const Person& lhs, const Person& rhs) {
        return lhs.age < rhs.age;
      }
  );
  return middle->age;
}*/

void PrintStats(vector<Person> persons) {
  cout << "Median age = " << ComputeMedianAge(begin(persons), end(persons)) << '\n';
  auto gender_bound = partition(begin(persons), end(persons), [](const Person& p) {
    return p.gender == Gender::FEMALE;
  });
  cout << "Median age for females = " << ComputeMedianAge(begin(persons), gender_bound) << '\n';
  cout << "Median age for males = " << ComputeMedianAge(gender_bound, end(persons)) << '\n';
  auto employed_female_bound = partition(begin(persons), gender_bound, [](const Person& p) {
    return p.is_employed;
  });
  cout << "Median age for employed females = " << ComputeMedianAge(begin(persons), employed_female_bound) << '\n';
  cout << "Median age for unemployed females = " << ComputeMedianAge(employed_female_bound, gender_bound) << '\n';
  auto employed_male_bound = partition(gender_bound, end(persons), [](const Person& p) {
    return p.is_employed;
  });
  cout << "Median age for employed males = " << ComputeMedianAge(gender_bound, employed_male_bound) << '\n';
  cout << "Median age for unemployed males = " << ComputeMedianAge(employed_male_bound, end(persons)) << '\n';
}

int main() {
  vector<Person> persons = {
      {31, Gender::MALE, false},
      {40, Gender::FEMALE, true},
      {24, Gender::MALE, true},
      {20, Gender::FEMALE, true},
      {80, Gender::FEMALE, false},
      {78, Gender::MALE, false},
      {10, Gender::FEMALE, false},
      {55, Gender::MALE, true},
  };
  PrintStats(persons);
  return 0;
}
