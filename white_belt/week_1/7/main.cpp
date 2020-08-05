#include <iostream>
#include <string>

int main() {
  std::string str;
  std::cin >> str;
  int index = -2;
  for (auto i = 0; i < str.size(); ++i) {
    if (str[i] == 'f') {
      if (index == -2) {
        index = -1;
      } else if (index == -1) {
        index = i;
      }
    }
  }
  std::cout << index;
  return 0;
}
