#include <iostream>
#include <string>
#include <vector>

struct student_t {
  std::string firstName, lastName;
  unsigned int day, month, year;
};

int main5() {
  size_t n;
  std::cin >> n;
  std::vector<student_t> students;
  std::string firstName, lastName;
  unsigned int day, month, year;
  for (size_t i = 0; i < n; ++ i) {
    std::cin >> firstName >> lastName >> day >> month >> year;
    students.push_back({firstName, lastName, day, month, year});
  }
  std::cin >> n;
  std::string command;
  unsigned int studentNo;
  for (size_t i = 0; i < n; ++ i) {
    std::cin >> command >> studentNo;
    if (studentNo < 1 || studentNo > students.size() || (command != "name" && command != "date")) {
      std::cout << "bad request" << '\n';
      continue;
    }
    if (command == "name") {
      std::cout << students[studentNo - 1].firstName << ' ' << students[studentNo - 1].lastName << '\n';
    } else {
      std::cout << students[studentNo - 1].day << '.' << students[studentNo - 1].month
        << '.' << students[studentNo - 1].year << '\n';
    }
  }
  return 0;
}
