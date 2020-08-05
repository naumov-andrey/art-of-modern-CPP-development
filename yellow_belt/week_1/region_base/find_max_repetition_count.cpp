#include <string>
#include <map>
#include <vector>

std::tuple<const int64_t&, const std::string, const std::string, std::map<Lang, std::string>>
MakeRegionRank(const Region& region) {
  return std::tie(region.population, region.std_name, region.parent_std_name, region.names);
}

int FindMaxRepetitionCount(const std::vector<Region>& regions) {
  if (!regions.empty()) {
    std::vector<bool> isChecked(regions.size(), false);
    int max_repeats = 1;
    for (size_t i = 0; i < regions.size(); ++i) {
      if (!isChecked[i]) {
        int repeats = 1;
        for (size_t j = i + 1; j < regions.size(); ++j) {
          if (!isChecked[j] && MakeRegionRank(regions[i]) == MakeRegionRank(regions[j])) {
            ++repeats;
            isChecked[j] = true;
          }
        }
        max_repeats = std::max(max_repeats, repeats);
        isChecked[i] = true;
      }
    }
    return max_repeats;
  } else {
    return 0;
  }
}
