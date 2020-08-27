#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
  if (range_end - range_begin < 2) {
    return;
  }
  vector<typename RandomIt::value_type> v(make_move_iterator(range_begin), make_move_iterator(range_end));
  auto range_third = v.begin() + (range_end - range_begin) / 3;
  MergeSort(v.begin(), range_third);
  auto range_two_third = range_third + (range_end - range_begin) / 3;
  MergeSort(range_third, range_two_third);
  MergeSort(range_two_third, v.end());
  vector<typename RandomIt::value_type> temp1;
  merge(make_move_iterator(v.begin()), make_move_iterator(range_third),
        make_move_iterator(range_third), make_move_iterator(range_two_third),
        back_insert_iterator(temp1));
  merge(make_move_iterator(temp1.begin()), make_move_iterator(temp1.end()),
        make_move_iterator(range_two_third), make_move_iterator(v.end()),
        range_begin);
}

void TestIntVector() {
  vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
  MergeSort(begin(numbers), end(numbers));
  ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  return 0;
}
