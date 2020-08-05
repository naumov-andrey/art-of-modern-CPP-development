#include <iostream>

int main() {
  double n, a, b, x, y;
  std::cin >> n >> a >> b >> x >> y;
  double disc = 1.0;
  if (n > b) {
    disc = 1 - (y / 100);
  } else if (n > a) {
    disc = 1 - (x / 100);
  }
  std::cout << n * disc;
  return 0;
}
