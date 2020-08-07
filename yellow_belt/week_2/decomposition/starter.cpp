#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
  string query_type;
  is >> query_type;
  if (query_type == "NEW_BUS") {
    q.type = QueryType::NewBus;
    is >> q.bus;
    int stop_count;
    cin >> stop_count;
    q.stops.resize(stop_count);
    for (auto& i : q.stops) {
      is >> i;
    }
  } else if (query_type == "BUSES_FOR_STOP") {
    q.type = QueryType::BusesForStop;
    is >> q.stop;
  } else if (query_type == "STOPS_FOR_BUS") {
    q.type = QueryType::StopsForBus;
    is >> q.bus;
  } else if (query_type == "ALL_BUSES") {
    q.type = QueryType::AllBuses;
  }
  return is;
}

struct BusesForStopResponse {
  bool isExist;
  string stop;
  vector<string> buses;
};

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

struct StopsForBusResponse {
  bool isExist;
  string bus;
  vector<BusesForStopResponse> stops;
};

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

struct AllBusesResponse {
  map<string, vector<string>> stops_for_buses;
};

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

class BusManager {
public:
  void AddBus(const string& bus, const vector<string>& stops) {
    stops_for_buses[bus] = stops;
    for (const auto& i : stops) {
      buses_for_stops[i].push_back(bus);
    }
  }

  BusesForStopResponse GetBusesForStop(const string& stop) const {
    if (buses_for_stops.count(stop) != 0) {
      return {true, stop, buses_for_stops.at(stop)};
    }
    return {false};
  }

  StopsForBusResponse GetStopsForBus(const string& bus) const {
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

  AllBusesResponse GetAllBuses() const {
    return {stops_for_buses};
  }

private:
  map<string, vector<string>> stops_for_buses, buses_for_stops;
};


int main() {
  int query_count;
  Query q;

  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
    switch (q.type) {
      case QueryType::NewBus:
        bm.AddBus(q.bus, q.stops);
        break;
      case QueryType::BusesForStop:
        cout << bm.GetBusesForStop(q.stop) << endl;
        break;
      case QueryType::StopsForBus:
        cout << bm.GetStopsForBus(q.bus) << endl;
        break;
      case QueryType::AllBuses:
        cout << bm.GetAllBuses() << endl;
        break;
    }
  }

  return 0;
}
