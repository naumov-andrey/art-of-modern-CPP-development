#include "database.h"

void Database::Add(const Date& date, const string& event) {
  auto it = find(records_[date].begin(), records_[date].end(), event);
  if (it == records_[date].end()) {
    records_[date].push_back(event);
  }
}

void Database::Print(ostream& os) const {
  for (const auto& i : records_) {
    for (const auto& j : i.second) {
      os << i.first << ' ' << j << '\n';
    }
  }
}

pair<Date, string> Database::Last(const Date& date) const {
  auto it = records_.upper_bound(date);
  if (it == records_.begin()) {
    throw invalid_argument("No events for this date");
  }
  --it;
  return make_pair(it->first, it->second.back());
}


ostream& operator << (ostream& os, const pair<Date, string>& record) {
  return os << record.first << ' ' << record.second;
}
