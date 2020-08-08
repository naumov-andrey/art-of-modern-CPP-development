#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

template <typename T>
vector<T> FindGreaterElements(const set<T>& elements, const T& border) {
  auto i = find_if(begin(elements), end(elements), [border](const T& elem) {
    return elem > border;
  });
  return vector<T>(i, end(elements));
}

int main() {
  for (int x : FindGreaterElements(set<int>{1, 5, 7, 8}, 5)) {
    cout << x << " ";
  }
  cout << endl;

  string to_find = "Python";
  cout << FindGreaterElements(set<string>{"C", "C++"}, to_find).size() << endl;
  return 0;
}
