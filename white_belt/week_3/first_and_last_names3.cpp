#include <string>
#include <map>
#include <vector>

class Person {
public:
  Person(const std::string& firstName, const std::string& lastName, unsigned int year)
  {
    firstNameEvents_[year] = firstName;
    lastNameEvents_[year] = lastName;
    birthYear = year;
  }

  void ChangeFirstName(int year, const std::string& first_name)
  {
    if (isAfterBirth(year)) {
      firstNameEvents_[year] = first_name;
    }
  }

  void ChangeLastName(int year, const std::string& last_name)
  {
    if (isAfterBirth(year)) {
      lastNameEvents_[year] = last_name;
    }
  }

  std::string GetFullName(int year) const
  {
    if (isAfterBirth(year)) {
      std::string firstName = getName(firstNameEvents_, year);
      std::string lastName = getName(lastNameEvents_, year);
      return FormFullName(firstName, lastName);
    }
    return "No person";
  }

  std::string GetFullNameWithHistory(int year) const
  {
    if (isAfterBirth(year)) {
      std::string firstName = getNameWithHistory(firstNameEvents_, year);
      std::string lastName = getNameWithHistory(lastNameEvents_, year);
      return FormFullName(firstName, lastName);
    }
    return "No person";
  }

private:
  std::map<int, std::string> firstNameEvents_;
  std::map<int, std::string> lastNameEvents_;
  unsigned int birthYear;

  bool isAfterBirth(int year) const
  {
    return year >= birthYear;
  }

  std::string getName(const std::map<int, std::string>& names, int year) const
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

  std::string getNameWithHistory(const std::map<int, std::string>& names, int year) const
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
    history.push_back(name);
    return FormNameWithHistory(history);
  }

  std::string FormNameWithHistory(const std::vector<std::string>& history) const
  {
    std::string name = history[history.size() - 1];
    if (history.size() > 1) {
      name += " (" + history[history.size() - 2];
      for (int i = history.size() - 3; i >= 0; --i) {
        name += ", " + history[i];
      }
      name += ")";
    }
    return name;
  }

  std::string FormFullName(const std::string& firstName, const std::string& lastName) const
  {
    if (firstName.empty() && lastName.empty()) {
      return "Incognito";
    } else if (firstName.empty()) {
      return lastName + " with unknown first name";
    } else if (lastName.empty()) {
      return firstName + " with unknown last name";
    }
    return firstName + ' ' + lastName;
  }
};
