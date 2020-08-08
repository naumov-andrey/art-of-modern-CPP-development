#include "responses.h"

#include <iostream>
using namespace std;

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
  if (r.isExist) {
    for (const auto& i : r.buses) {
      os << i << ' ';
    }
  } else {
    os << "No stop";
  }
  return os;
}

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
  if (r.isExist) {
    bool isFirst = true;
    for (const auto& i : r.stops) {
      if (!isFirst) {
        os << '\n';
      }
      isFirst = false;
      os << "Stop " << i.stop << ':';
      if (i.buses.size() > 1) {
        for (const auto& j : i.buses) {
          if (j != r.bus) {
            os << ' ' << j;
          }
        }
      } else {
        os << " no interchange";
      }
    }
  } else {
    os << "No bus";
  }
  return os;
}

ostream& operator << (ostream& os, const AllBusesResponse& r) {
  if (!r.stops_for_buses.empty()) {
    bool isFirst = true;
    for (const auto& i : r.stops_for_buses) {
      if (!isFirst) {
        os << '\n';
      }
      isFirst = false;
      os << "Bus " << i.first << ':';
      for (const auto& j : i.second) {
        os << ' ' << j;
      }
    }
  } else {
    os << "No buses";
  }
  return os;
}
