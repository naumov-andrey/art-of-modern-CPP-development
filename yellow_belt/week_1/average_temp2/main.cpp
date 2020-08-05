#include <iostream>
#include <vector>

int main() {
  int n;
  std::cin >> n;
  int temp_value;
  long long int sum = 0;
  std::vector<int> t;
  for (int i = 0; i < n; ++i) {
    std::cin >> temp_value;
    sum += temp_value;
    t.push_back(temp_value);
  }

  int average = sum / n;
  std::vector<int> days;
  for (int i = 0; i < n; ++i) {
    if (t[i] > average) {
      days.push_back(i);
    }
  }

  std::cout << days.size() << '\n';
  for (const auto& i : days) {
    std::cout << i << ' ';
  }
  return 0;
}
