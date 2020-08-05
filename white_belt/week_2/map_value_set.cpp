#include <string>
#include <set>
#include <map>

std::set<std::string> BuildMapValuesSet(const std::map<int, std::string>& m) {
  std::set<std::string> result;
  for (const auto& i : m) {
    result.insert(i.second);
  }
  return result;
}
