#include <vector>
#include <string>

std::vector<std::string> PalindromFilter(std::vector<std::string> words, int minLength) {
  std::vector<std::string> palindroms;
  for (auto str : words) {
    if (str.size() >= minLength) {
      palindroms.push_back(str);
      for (int i = 0; i < str.size() / 2; ++i) {
        if (str[i] != str[str.size() - 1 - i]) {
          palindroms.pop_back();
          break;
        }
      }
    }
  }
  return palindroms;
}
