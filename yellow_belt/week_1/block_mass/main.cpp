#include <iostream>

int main() {
  int n, r;
  std::cin >> n >> r;
  uint64_t v = 0;
  int w, h, d;
  for (int i = 0; i < n; ++i) {
    std::cin >> w >> h >> d;
      v += static_cast<uint64_t>(w) * static_cast<uint64_t>(h) * d;
  }
  std::cout << v * r;
  return 0;
}
