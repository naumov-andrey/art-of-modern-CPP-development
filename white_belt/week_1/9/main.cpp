#include <iostream>
#include <vector>

int main() {
  unsigned int n;
  std::cin >> n;
  std::vector<short> binaryN;
  while (n != 0) {
    binaryN.push_back(n % 2);
    n /= 2;
  }
  for (int i = binaryN.size() - 1; i >= 0; --i) {
    std::cout << binaryN[i];
  }
  return 0;
}
