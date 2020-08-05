#include <vector>
#include <iostream>
#include <string>

int main4() {
  size_t n;
  std::cin >> n;
  unsigned short currentMonth = 0;
  const std::vector<unsigned short> daysPerMonth = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  std::vector<std::vector<std::string>> affairs(daysPerMonth[currentMonth]);
  for (size_t i = 0; i < n; ++i) {
    std::string command;
    std::cin >> command;
    if (command == "ADD") {
      std::string s;
      size_t index;
      std::cin >> index >> s;
      affairs[index - 1].push_back(s);
    } else if (command == "DUMP") {
      size_t index;
      std::cin >> index;
      std::cout << affairs[index - 1].size() << ' ';
      for (std::string j : affairs[index - 1]) {
        std::cout << j << ' ';
      }
      std::cout << '\n';
    } else {
      unsigned short nextMonth = (currentMonth + 1) % 12;
      if (daysPerMonth[currentMonth] > daysPerMonth[nextMonth]) {
        for (unsigned short j = daysPerMonth[nextMonth]; j < daysPerMonth[currentMonth]; ++j) {
          affairs[daysPerMonth[nextMonth] - 1].insert(affairs[daysPerMonth[nextMonth] - 1].end(),
                                                      affairs[j].begin(), affairs[j].end());
        }
      }
      currentMonth = nextMonth;
      affairs.resize(daysPerMonth[currentMonth]);
    }
  }
}
