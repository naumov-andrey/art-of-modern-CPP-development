#include "bus_manager.h"

using namespace std;

void BusManager::AddBus(const string& bus, const vector<string>& stops) {
  stops_for_buses[bus] = stops;
  for (const auto& i : stops) {
    buses_for_stops[i].push_back(bus);
  }
}

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
  if (buses_for_stops.count(stop) != 0) {
    return {true, stop, buses_for_stops.at(stop)};
  }
  return {false};
}

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
  if (stops_for_buses.count(bus) != 0) {
    vector<BusesForStopResponse> stops;
    stops.reserve(stops_for_buses.at(bus).size());
    for (const auto& i : stops_for_buses.at(bus)) {
      stops.push_back(GetBusesForStop(i));
    }
    return {true, bus, stops};
  }
  return {false};
}

AllBusesResponse BusManager::GetAllBuses() const {
  return {stops_for_buses};
}
