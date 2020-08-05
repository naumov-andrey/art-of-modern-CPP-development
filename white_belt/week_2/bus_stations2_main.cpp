#include <iostream>
#include <map>
#include <vector>
#include <string>

int main8()
{
  size_t q;
  std::cin >> q;
  std::map<std::vector<std::string>, unsigned int> routes;
  for (size_t i = 0; i < q; ++i) {
    size_t n;
    std::cin >> n;
    std::vector<std::string> stops;
    for (size_t j = 0; j < n; ++j) {
      std::string stop;
      std::cin >> stop;
      stops.push_back(stop);
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
