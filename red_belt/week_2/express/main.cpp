#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <set>

using namespace std;

class RouteManager {
public:
  void AddRoute(int start, int finish) {
    reachable_lists_[start].insert(finish);
    reachable_lists_[finish].insert(start);
  }
  int FindNearestFinish(int start, int finish) const {
    if (reachable_lists_.count(start) < 1) {
      return abs(start - finish);
    }
    const set<int>& reachable = reachable_lists_.at(start);
    auto nearest = reachable.lower_bound(finish);
    if (nearest != reachable.begin()) {
      if (nearest == reachable.end() || abs(*nearest - finish) > abs(*prev(nearest) - finish)) {
        nearest = prev(nearest);
      }
    }
    return min(abs(start - finish), abs(*nearest - finish));
  }
private:
  map<int, set<int>> reachable_lists_;
};


int main() {
  RouteManager routes;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int start, finish;
    cin >> start >> finish;
    if (query_type == "ADD") {
      routes.AddRoute(start, finish);
    } else if (query_type == "GO") {
      cout << routes.FindNearestFinish(start, finish) << "\n";
    }
  }

  return 0;
}
