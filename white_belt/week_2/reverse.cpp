#include <vector>

void Reverse(std::vector<int>& v) {
  for (auto i = 0; i < v.size() / 2; ++i) {
    std::swap(v[i], v[v.size() - 1 - i]);
  }
}
