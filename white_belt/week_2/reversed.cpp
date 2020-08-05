#include <vector>

std::vector<int> Reversed(const std::vector<int>& v) {
  std::vector<int> reversed = v;
  for (auto i = 0; i < reversed.size() / 2; ++i) {
    std::swap(reversed[i], reversed[v.size() - 1 - i]);
  }
  return reversed;
}
