#include <string>
#include <map>
#include <vector>

class Person {
public:
  void ChangeFirstName(int year, const std::string& first_name) {
    firstNameEvents_[year] = first_name;
  }

  void ChangeLastName(int year, const std::string& last_name) {
    lastNameEvents_[year] = last_name;
  }

  std::string GetFullName(int year) {
    std::string firstName = getName(firstNameEvents_, year);
    std::string lastName = getName(lastNameEvents_, year);
    if (firstName.empty() && lastName.empty()) {
      return "Incognito";
    } else if (firstName.empty()) {
      return lastName + " with unknown first name";
    } else if (lastName.empty()) {
      return firstName + " with unknown last name";
    }
    return firstName + ' ' + lastName;
  }

  std::string GetFullNameWithHistory(int year) {
    std::string firstName = getFullName(firstNameEvents_, year);
    std::string lastName = getFullName(lastNameEvents_, year);
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
  std::map<int, std::string> firstNameEvents_;
  std::map<int, std::string> lastNameEvents_;

  std::string getName(const std::map<int, std::string>& names, int year)
  {
    std::string name;
    for (const auto& i : names) {
      if (i.first <= year) {
        name = i.second;
      } else {
        break;
      }
    }
    return name;
  }

  std::string getFullName(const std::map<int, std::string>& names, int year)
  {
    std::string name;
    std::vector<std::string> history;
    for (const auto& i : names) {
      if (i.first <= year) {
        if (!name.empty() && name != i.second) {
          history.push_back(name);
        }
        name = i.second;
      } else {
        break;
      }
    }
    if (!history.empty()) {
      name += " (" + history[history.size() - 1];
      for (int i = history.size() - 2; i >= 0; --i) {
        name += ", " + history[i];
      }
      name += ")";
    }
    return name;
  }
};
