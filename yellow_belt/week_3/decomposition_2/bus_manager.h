#pragma once

#include <map>
#include <vector>
#include <string>
#include "responses.h"
using namespace std;

class BusManager {
public:
  void AddBus(const string& bus, const vector<string>& stops);

  BusesForStopResponse GetBusesForStop(const string& stop) const;

  StopsForBusResponse GetStopsForBus(const string& bus) const;

  AllBusesResponse GetAllBuses() const;

private:
  map<string, vector<string>> stops_for_buses, buses_for_stops;
};
