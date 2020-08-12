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
    int removed = 0;
    for (auto it = chronology_.begin(); it != chronology_.end();) {
      auto new_end = stable_partition(it->second.begin(), it->second.end(), [it, predicate](const auto& ev) {
        return !predicate(it->first, ev);
      });
      removed += it->second.end() - new_end;
      if (new_end == it->second.begin()) {
        records_.erase(it->first);
        it = chronology_.erase(it);
      } else {
        for (auto j = new_end; j != it->second.end(); ++j) {
          records_[it->first].erase(*j);
        }
        it->second.erase(new_end, it->second.end());
        ++it;
      }
    }
    return removed;
  }

  template<typename Predicate> vector<pair<Date, string>> FindIf(Predicate predicate) const {
    vector<pair<Date, string>> satisfying;
    for (const auto& i : chronology_) {
      for (const auto& j: i.second) {
        if (predicate(i.first, j)) {
          satisfying.emplace_back(i.first, j);
        }
      }
    }
    return satisfying;
  }

private:
  map<Date, set<string>> records_;
  map<Date, vector<string>> chronology_;
};

ostream& operator << (ostream& os, const pair<Date, string>& record);

void TestDatabase();
