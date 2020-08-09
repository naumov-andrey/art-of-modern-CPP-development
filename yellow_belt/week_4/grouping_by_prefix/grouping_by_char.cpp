#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, char prefix) {
  auto lower = lower_bound(range_begin, range_end, prefix, [](auto str, auto value) {
        return value > str[0];
  });
  auto upper = upper_bound(range_begin, range_end, prefix, [](auto value, auto str) {
        return str[0] > value;
  });
  return make_pair(lower, upper);
}

int main() {
  const vector<string> sorted_strings = {"moscow", "murmansk", "vologda"};

  const auto m_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), 'm');
  for (auto it = m_result.first; it != m_result.second; ++it) {
    cout << *it << " ";
  }
  cout << endl;

  const auto p_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), 'p');
  cout << (p_result.first - begin(sorted_strings)) << " " <<
       (p_result.second - begin(sorted_strings)) << endl;

  const auto z_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), 'z');
  cout << (z_result.first - begin(sorted_strings)) << " " <<
       (z_result.second - begin(sorted_strings)) << endl;

  return 0;
}
