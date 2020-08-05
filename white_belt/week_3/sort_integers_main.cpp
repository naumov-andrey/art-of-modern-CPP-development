#include <iostream>
#include <vector>
#include <algorithm>

bool compareModulo(int a, int b)
{
  return std::abs(a) < std::abs(b);
}

int main1() {
  unsigned int n;
  std::cin >> n;
  std::vector<int> numbers;
  for (auto i = 0; i < n; ++i) {
    int num;
    std::cin >> num;
    numbers.push_back(num);
  }
  std::sort(std::begin(numbers), std::end(numbers), compareModulo);
  for (const auto& i : numbers) {
    std::cout << i << ' ';
  }
  return 0;
}
