#include <iostream>
#include <string>
#include <map>

std::map<char, int> BuildCharCounters(const std::string& str)
{
  std::map<char, int> m;
  for (auto i : str) {
    ++m[i];
  }
  return m;
}

int main5()
{
  size_t n;
  std::cin >> n;
  for (size_t i = 0; i < n; ++i) {
    std::string first, second;
    std::cin >> first >> second;
    std::map<char, int> firstLetters = BuildCharCounters(first), secondLetters = BuildCharCounters(second);
    if (firstLetters == secondLetters) {
      std::cout << "YES" << '\n';
    } else {
      std::cout << "NO" << '\n';
    }
  }
  return 0;
}
