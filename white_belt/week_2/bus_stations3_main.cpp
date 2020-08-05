#include <iostream>
#include <string>
#include <set>
#include <map>

int main()
{
  size_t q;
  std::cin >> q;
  std::map<std::set<std::string>, unsigned int> routes;
  for (size_t i = 0; i < q; ++i) {
    size_t n;
    std::cin >> n;
    std::set<std::string> stops;
    for (size_t j = 0; j < n; ++j) {
      std::string stop;
      std::cin >> stop;
      stops.insert(stop);
    }
    if (routes.count(stops) == 0) {
      routes[stops] = routes.size() + 1;
      std::cout << "New bus " << routes.size() << '\n';
    } else {
      std::cout << "Already exists for " << routes[stops] << '\n';
    }
  }
  return 0;
}
