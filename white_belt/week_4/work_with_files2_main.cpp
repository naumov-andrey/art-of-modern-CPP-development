#include <fstream>
#include <iostream>
#include <string>

int main2() {
  std::ifstream input("input.txt");
  if (input) {
    std::ofstream output("output.txt");
    std::string line;
    while (std::getline(input, line)) {
      output << line << '\n';
    }
  }
  return 0;
}
