#pragma once

#include "date.h"

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

class Database {
public:
  void Add(const Date& date, const string& event);
  void Print(ostream& os) const;
  pair<Date, string> Last(const Date& date) const;

  template<typename Predicate> int RemoveIf(Predicate predicate) {
    int to_delete = 0;
    map<Date, vector<string>> new_records;
    for (auto& rec : records_) {
      Date date = rec.first;
      auto it = remove_if(rec.second.begin(), rec.second.end(), [date, predicate](const auto& event) {
        return predicate(date, event);
      });
      to_delete += rec.second.end() - it;
      if (it != rec.second.begin()) {
        new_records[date] = rec.second;
      }
    }
    records_ = new_records;
    return to_delete;
  }

  template<typename Predicate> vector<pair<Date, string>> FindIf(Predicate predicate) const {
    vector<pair<Date, string>> satisfying;
    for (const auto& rec : records_) {
      for (const auto& ev: rec.second) {
        if (predicate(rec.first, ev)) {
          satisfying.emplace_back(rec.first, ev);
        }
      }
    }
    return satisfying;
  }

private:
  map<Date, vector<string>> records_;
};

ostream& operator << (ostream& os, const pair<Date, string>& record);

void TestDatabase();
