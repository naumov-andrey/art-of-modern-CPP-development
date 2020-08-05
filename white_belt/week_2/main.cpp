#include <iostream>
#include <string>
#include <vector>

int Factorial(int n);
bool IsPalindrom(std::string str);
std::vector<std::string> PalindromFilter(std::vector<std::string> words, int minLength);
void UpdateIfGreater(const int& first, int& second);
void MoveStrings(std::vector<std::string>& src, std::vector<std::string>& dst);
void Reverse(std::vector<int>& v);
std::vector<int> Reversed(const std::vector<int>& v);

int main1() {
  /*std::cout << Factorial(1) << '\n';
  std::cout << Factorial(-2) << '\n';
  std::cout << Factorial(4) << '\n';*/

  /*std::cout << IsPalindrom("madam") << '\n';
  std::cout << IsPalindrom("gentlemen") << '\n';
  std::cout << IsPalindrom("X") << '\n';*/

  /*std::vector<std::string> p = PalindromFilter({"abacaba", "aba"}, 5);
  //std::vector<std::string> p = PalindromFilter({"abacaba", "aba"}, 2);
  //std::vector<std::string> p = PalindromFilter({"weew", "bro", "code"}, 4);
  for (auto i : p) {
    std::cout << i << ' ';
  }*/

  /*int a = 4, b = 2;
  UpdateIfGreater(a, b);
  std::cout << b << '\n';
  UpdateIfGreater(5, b);
  std::cout << b << '\n';*/

  /*std::vector<std::string> source = {"a", "b", "c"};
  std::vector<std::string> destination = {"z"};
  MoveStrings(source, destination);
  for (auto i : source) {
    std::cout << i << ' ';
  }
  for (auto i : destination) {
    std::cout << i << ' ';
  }*/

  /*std::vector<int> numbers = {1, 5, 3, 4, 2};
  Reverse(numbers);
  for (auto i : numbers) {
    std::cout << i << ' ';
  }*/

  /*std::vector<int> numbers = {1, 5, 3, 4, 2};
  std::vector<int> reversedNumbers = Reversed(numbers);
  for (auto i : numbers) {
    std::cout << i << ' ';
  }
  for (auto i : reversedNumbers) {
    std::cout << i << ' ';
  }*/

  return 0;
}
