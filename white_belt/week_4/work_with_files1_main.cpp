#include <fstream>
#include <iostream>
#include <string>

int main1() {
  std::ifstream input("input.txt");
  if (input) {
    std::string line;
    while (std::getline(input, line)) {
      std::cout << line << '\n';
    }
  }
  return 0;
}
