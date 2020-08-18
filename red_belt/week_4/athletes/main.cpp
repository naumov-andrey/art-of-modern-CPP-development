#include <iostream>
#include <list>
#include <map>
using namespace std;

int main() {
  cin.tie(nullptr);
  ios_base::sync_with_stdio(false);

  int n;
  cin >> n;
  list<int> athletes;
  map<int, list<int>::iterator> pos_for_athlete;
  int before, current;
  for (int i = 0; i < n; ++i) {
    cin >> current >> before;
    if (pos_for_athlete.count(before) == 0) {
      pos_for_athlete[current] = athletes.insert(athletes.end(), current);
    } else {
      pos_for_athlete[current] = athletes.insert(pos_for_athlete[before], current);
    }
  }
  for (auto i : athletes) {
    cout << i << '\n';
  }
  return 0;
}
