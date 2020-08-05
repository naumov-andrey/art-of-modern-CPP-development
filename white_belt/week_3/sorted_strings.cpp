#include <string>
#include <vector>
#include <algorithm>

class SortedStrings {
public:
  void AddString(const std::string& s) {
    sortedStrings_.push_back(s);
    std::sort(std::begin(sortedStrings_), std::end(sortedStrings_));
  }
  std::vector<std::string> GetSortedStrings() { return sortedStrings_;}
private:
  std::vector<std::string> sortedStrings_;
};
