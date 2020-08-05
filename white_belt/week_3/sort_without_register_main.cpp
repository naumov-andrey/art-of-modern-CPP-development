#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

int main2()
{
  unsigned int n;
  std::cin >> n;
  std::vector<std::string> strings;
  for (auto i = 0; i < n; ++i) {
    std::string str;
    std::cin >> str;
    strings.push_back(str);
  }
  std::sort(std::begin(strings), std::end(strings), [](std::string a, std::string b)
  {
    std::string c, d;
    for (const auto& i : a) {
      c += std::tolower(i);
    }
    for (const auto& i : b) {
      d += std::tolower(i);
    }
    return c < d;
  });
  for (const auto& i : strings) {
    std::cout << i << ' ';
  }
  return 0;
}
