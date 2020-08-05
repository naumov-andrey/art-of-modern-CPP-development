#include <iostream>
#include <string>
#include <map>
#include <vector>

int main7()
{
  size_t n;
  std::cin >> n;
  std::map<std::string, std::vector<std::string>> buses;
  std::map<std::string, std::vector<std::string>> stops;
  for (size_t i = 0; i < n; ++i) {
    std::string command;
    std::cin >> command;
    if (command == "NEW_BUS") {
      std::string bus;
      size_t count;
      std::cin >> bus >> count;
      for (size_t j = 0; j < count; ++j) {
        std::string stop;
        std::cin >> stop;
        buses[bus].push_back(stop);
        stops[stop].push_back(bus);
      }
    } else if (command == "BUSES_FOR_STOP") {
      std::string stop;
      std::cin >> stop;
      if (stops.count(stop) == 0) {
        std::cout << "No stop" << '\n';
      } else {
        for (const auto& j : stops[stop]) {
          std::cout << j << ' ';
        }
        std::cout << '\n';
      }
    } else if (command == "STOPS_FOR_BUS") {
      std::string bus;
      std::cin >> bus;
      if (buses.count(bus) == 0) {
        std::cout << "No bus" << '\n';
      } else {
        for (const auto& j : buses[bus]) {
          std::cout << "Stop " << j << ": ";
          if (stops[j].size() == 1) {
            std::cout << "no interchange";
          } else {
            for (const auto& k : stops[j]) {
              if (k != bus) {
                std::cout << k << ' ';
              }
            }
          }
          std::cout << '\n';
        }
      }
    } else if (command == "ALL_BUSES") {
      if (buses.empty()) {
        std::cout << "No buses" << '\n';
      } else {
        for (const auto& j : buses) {
          std::cout << "Bus " << j.first << ": ";
          for (const auto& k : j.second) {
            std::cout << k << ' ';
          }
          std::cout << '\n';
        }
      }
    }
  }
  return 0;
}
