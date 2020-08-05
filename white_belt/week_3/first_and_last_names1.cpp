#include <string>
#include <vector>
#include <algorithm>

class Person {
public:
  void ChangeFirstName(int year, const std::string& first_name) {
    firstNameEvents_.emplace_back(year, first_name);
  }
  void ChangeLastName(int year, const std::string& last_name) {
    lastNameEvents_.emplace_back(year, last_name);
  }
  std::string GetFullName(int year) {
    std::string firstName;
    if (!firstNameEvents_.empty()) {
      std::sort(std::begin(firstNameEvents_), std::end(firstNameEvents_), [](auto a, auto b) {
        return a.first < b.first;
      });
      for (const auto& i : firstNameEvents_) {
        if (i.first <= year) {
          firstName = i.second;
        } else {
          break;
        }
      }
    }
    std::string lastName;
    if (!lastNameEvents_.empty()) {
      std::sort(std::begin(lastNameEvents_), std::end(lastNameEvents_), [](auto a, auto b) {
        return a.first < b.first;
      });
      for (const auto& i : lastNameEvents_) {
        if (i.first <= year) {
          lastName = i.second;
        } else {
          break;
        }
      }
    }
    if (firstName.empty() && lastName.empty()) {
      return "Incognito";
    } else if (firstName.empty()) {
      return lastName + " with unknown first name";
    } else if (lastName.empty()) {
      return firstName + " with unknown last name";
    }
    return firstName + ' ' + lastName;
  }
private:
  std::vector<std::pair<int, std::string>> firstNameEvents_;
  std::vector<std::pair<int, std::string>> lastNameEvents_;
};
