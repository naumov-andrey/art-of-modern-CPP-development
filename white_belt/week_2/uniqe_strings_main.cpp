#include <iostream>
#include <string>
#include <set>

int main9()
{
  size_t n;
  std::cin >> n;
  std::set<std::string> uniqueStrings;
  for (size_t i = 0; i < n; ++i) {
    std::string str;
    std::cin >> str;
    uniqueStrings.insert(str);
  }
  std::cout << uniqueStrings.size();
  return 0;
}
