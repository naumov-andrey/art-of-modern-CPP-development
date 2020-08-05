#include <iostream>
#include <vector>

int main2() {
  size_t n;
  std::cin >> n;
  std::vector<unsigned int> temps(n);
  unsigned int average = 0;
  for (size_t i = 0; i < n; ++i) {
    unsigned int tmp;
    std::cin >> tmp;
    average += tmp;
    temps[i] = tmp;
  }
  average /= n;
  std::vector<size_t> daysWithHighTemp;
  for (size_t i = 0; i < n; ++i) {
    if (temps[i] > average) {
      daysWithHighTemp.push_back(i);
    }
  }
  std::cout << daysWithHighTemp.size() << '\n';
  for (size_t i : daysWithHighTemp) {
    std::cout << i << ' ';
  }
  return 0;
}
