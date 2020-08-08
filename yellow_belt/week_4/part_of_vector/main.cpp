#include <iostream>
#include <vector>
using namespace std;

void PrintVectorPart(const vector<int>& numbers) {
  auto i = numbers.begin();
  for (; i != numbers.end(); ++i) {
    if (*i < 0) {
      break;
    }
  }
  while (i != numbers.begin()) {
    --i;
    cout << *i << ' ';
  }
}

int main() {
  PrintVectorPart({6, 1, 8, -5, 4});
  cout << endl;
  PrintVectorPart({-6, 1, 8, -5, 4});  // ничего не выведется
  cout << endl;
  PrintVectorPart({6, 1, 8, 5, 4});
  cout << endl;
  return 0;
}
