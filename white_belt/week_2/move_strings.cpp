#include <string>
#include <vector>

void MoveStrings(std::vector<std::string>& src, std::vector<std::string>& dst) {
  for (auto i : src) {
    dst.push_back(i);
  }
  src.clear();
}
