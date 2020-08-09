#include <iostream>
#include <set>

using namespace std;

set<int>::const_iterator FindNearestElement(const set<int>& numbers, int border) {
  if (numbers.begin() == numbers.end()) {
    return numbers.end();
  }
  auto left_bound = numbers.begin(), right_bound = next(left_bound);
  while (right_bound != numbers.end()) {
    if (border <= *right_bound) {
      if (abs(*left_bound - border) <= abs(*right_bound - border)) {
        return left_bound;
      }
      return right_bound;
    }
    left_bound = right_bound;
    right_bound = next(right_bound);
  }
  return left_bound;
}

int main() {
  set<int> numbers = {1, 4, 6};
  cout <<
       *FindNearestElement(numbers, 0) << " " <<
       *FindNearestElement(numbers, 3) << " " <<
       *FindNearestElement(numbers, 5) << " " <<
       *FindNearestElement(numbers, 6) << " " <<
       *FindNearestElement(numbers, 100) << endl;

  set<int> empty_set;

  cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
  return 0;
}
