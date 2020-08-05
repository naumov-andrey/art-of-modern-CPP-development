#include <vector>
#include <iostream>
#include <string>

int main3() {
  size_t n;
  std::cin >> n;
  std::vector<bool> queue;
  for (size_t i = 0; i < n; ++i) {
    std::string command;
    std::cin >> command;
    if (command == "WORRY") {
      size_t index;
      std::cin >> index;
      queue[index] = true;
    } else if (command == "QUIET") {
      size_t index;
      std::cin >> index;
      queue[index] = false;
    } else if (command == "COME") {
      int count;
      std::cin >> count;
      queue.resize(queue.size() + count);
    } else {
      size_t count = 0;
      for (bool i : queue) {
        if (i) {
          ++count;
        }
      }
      std::cout << count << '\n';
    }
  }
}
