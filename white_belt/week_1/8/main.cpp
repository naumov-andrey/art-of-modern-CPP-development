#include <iostream>

int main() {
  unsigned int a, b;
  std::cin >> a >> b;
  while (a != b && a != 0 && b != 0) {
    if (a > b) {
      a = a % b;
    } else {
      b = b % a;
    }
  }
  std::cout << std::max(a, b);
  return 0;
}
