#include <iostream>
#include <map>
#include <string>

int main6()
{
  size_t n;
  std::cin >> n;
  std::map<std::string, std::string> countryCapitals;
  for (size_t i = 0; i < n; ++i) {
    std::string command;
    std::cin >> command;
    if (command == "CHANGE_CAPITAL") {
      std::string country, capital;
      std::cin >> country >> capital;
      if (countryCapitals.count(country) == 0) {
        std::cout << "Introduce new country " << country << " with capital " << capital << '\n';
      } else {
        if (countryCapitals[country] == capital) {
          std::cout << "Country " << country << " hasn't changed its capital" << '\n';
        } else {
          std::cout << "Country " << country << " has changed its capital from "
            << countryCapitals[country] << " to " << capital << '\n';
        }
      }
      countryCapitals[country] = capital;
    } else if (command == "RENAME") {
      std::string oldCountry, newCountry;
      std::cin >> oldCountry >> newCountry;
      if (oldCountry == newCountry || countryCapitals.count(oldCountry) == 0 || countryCapitals.count(newCountry) > 0) {
        std::cout << "Incorrect rename, skip" << '\n';
      } else {
        std::cout << "Country " << oldCountry << " with capital " << countryCapitals[oldCountry]
          << " has been renamed to " << newCountry << '\n';
        countryCapitals[newCountry] = countryCapitals[oldCountry];
        countryCapitals.erase(oldCountry);
      }
    } else if (command == "ABOUT") {
      std::string country;
      std::cin >> country;
      if (countryCapitals.count(country) == 0) {
        std::cout << "Country " << country << " doesn't exist" << '\n';
      } else {
        std::cout << "Country " << country << " has capital " << countryCapitals[country] << '\n';
      }
    } else if (command == "DUMP") {
      if (countryCapitals.empty()) {
        std::cout << "There are no countries in the world" << '\n';
      } else {
        for (const auto& j : countryCapitals) {
          std::cout << j.first << '/' << j.second << ' ';
        }
        std::cout << '\n';
      }
    }
  }
}
