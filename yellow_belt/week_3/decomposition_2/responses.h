#pragma once

#include <string>
#include <vector>
#include <map>
using namespace std;

struct BusesForStopResponse {
  bool isExist;
  string stop;
  vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r);

struct StopsForBusResponse {
  bool isExist;
  string bus;
  vector<BusesForStopResponse> stops;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r);

struct AllBusesResponse {
  map<string, vector<string>> stops_for_buses;
};

ostream& operator << (ostream& os, const AllBusesResponse& r);
