#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> numbers(n);
  for (int i = n; i > 0; --i) {
    numbers[n - i] = i;
  }
  do {
    for (const auto& i : numbers) {
      cout << i << ' ';
    }
    cout << '\n';
  } while (next_permutation(begin(numbers), end(numbers), [](const auto& lhs, const auto& rhs) {
    return lhs > rhs;
  }));
  return 0;
}
