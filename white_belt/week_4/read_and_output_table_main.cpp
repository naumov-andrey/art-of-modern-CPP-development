#include <iostream>
#include <fstream>
#include <iomanip>

int main4() {
  std::ifstream in("input.txt");
  if (in) {
    size_t n, m;
    in >> n >> m;
    std::cout << std::setfill(' ');
    int num;
    for (size_t i = 0; i < n; ++i) {
      in >> num;
      std::cout << std::setw(10) << num;
      for (size_t j = 1; j < m; ++j) {
        in.ignore(1);
        in >> num;
        std::cout << ' ' << std::setw(10) << num;
      }
      if (i != n - 1) {
        std::cout << '\n';
      }
    }
  }
  return 0;
}
