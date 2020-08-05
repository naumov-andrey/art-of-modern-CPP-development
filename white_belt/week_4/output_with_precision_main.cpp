#include <iostream>
#include <fstream>
#include <iomanip>

int main3() {
  std::ifstream in("input.txt");
  if (in) {
    double number;
    std::cout << std::fixed << std::setprecision(3);
    while (in >> number) {
      std::cout << number << '\n';
    }
  }
  return 0;
}
