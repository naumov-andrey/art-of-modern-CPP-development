#include "database.h"

void Database::Add(const Date& date, const string& event) {
  auto it = records_[date].insert(event);
  if (it.second) {
    chronology_[date].push_back(event);
  }
}

void Database::Print(ostream& os) const {
  for (const auto& i : chronology_) {
    for (const auto& j : i.second) {
      os << i.first << ' ' << j << '\n';
    }
  }
}

pair<Date, string> Database::Last(const Date& date) const {
  auto it = chronology_.upper_bound(date);
  if (it == chronology_.begin()) {
    throw invalid_argument("No events for this date");
  }
  --it;
  return make_pair(it->first, it->second.back());
}


ostream& operator << (ostream& os, const pair<Date, string>& record) {
  return os << record.first << ' ' << record.second;
}
