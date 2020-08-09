#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
  if (distance(range_begin, range_end) < 2) {
    return;
  }
  vector<typename RandomIt::value_type> elements(range_begin, range_end);
  RandomIt first_part_end = begin(elements) + elements.size() / 3;
  RandomIt second_part_end = first_part_end + elements.size() / 3;
  MergeSort(begin(elements), first_part_end);
  MergeSort(first_part_end, second_part_end);
  MergeSort(second_part_end, end(elements));
  vector<typename RandomIt::value_type> temp;
  merge(begin(elements), first_part_end, first_part_end, second_part_end, back_inserter(temp));
  merge(begin(temp), end(temp), second_part_end, end(elements), range_begin);
}

int main() {
  vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
  MergeSort(begin(v), end(v));
  for (int x : v) {
    cout << x << " ";
  }
  cout << endl;
  return 0;
}
