#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>
#include <map>
#include <set>

void ensureNextSymbolAndSkip(std::istream& in, char delimiter) {
  if (in.peek() == delimiter) {
    in.ignore(1);
  } else {
    throw std::domain_error("Wrong delimiter");
  }
}

class Date {
public:
  explicit Date(std::string str) {
    std::stringstream stringStream(str);
    try {
      stringStream >> year_;
      ensureNextSymbolAndSkip(stringStream, '-');
      stringStream >> month_;
      ensureNextSymbolAndSkip(stringStream, '-');
      stringStream >> day_;
      if (!stringStream.eof() || stringStream.fail()) {
        throw std::domain_error("Extra symbols");
      }
    } catch (std::domain_error&) {
      throw std::domain_error("Wrong date format: " + str);
    }
    validate();
  }

  int GetYear() const { return year_;}
  int GetMonth() const { return month_;}
  int GetDay() const { return day_;}

private:
  int year_;
  int month_;
  int day_;

  void validate() const {
    if (month_ < 1 || month_ > 12) {
      throw std::invalid_argument("Month value is invalid: " + std::to_string(month_));
    }
    if (day_ < 1 || day_ > 31) {
      throw std::invalid_argument("Day value is invalid: " + std::to_string(day_));
    }
  }
};

bool operator<(const Date& lhs, const Date& rhs) {
  if (lhs.GetYear() == rhs.GetYear()) {
    if (lhs.GetMonth() == rhs.GetMonth()) {
      return lhs.GetDay() < rhs.GetDay();
    }
    return lhs.GetMonth() < rhs.GetMonth();
  }
  return lhs.GetYear() < rhs.GetYear();
}

std::ostream& operator<<(std::ostream& out, const Date& d) {
  out << std::setw(4) << std::setfill('0') << d.GetYear()
      << '-'
      << std::setw(2) << std::setfill('0') << d.GetMonth()
      << '-'
      << std::setw(2) << std::setfill('0') << d.GetDay();
  return out;
}


class Database {
public:
  void AddEvent(const Date& date, const std::string& event) {
    if (!event.empty()) {
      records_[date].insert(event);
    }
  }

  bool DeleteEvent(const Date& date, const std::string& event) {
    if (records_.count(date) > 0 && records_[date].count(event) > 0) {
      records_[date].erase(event);
      return true;
    }
    return false;
  }

  int DeleteDate(const Date& date) {
    int n = 0;
    if (records_.count(date) > 0) {
      n = records_[date].size();
      records_.erase(date);
    }
    return n;
  }

  std::set<std::string> Find(const Date& date) const {
    if (records_.count(date) > 0) {
      return records_.at(date);
    }
    return {};
  }

  void Print() const {
    for (const auto& i : records_) {
      for (const auto& j : i.second) {
        std::cout << i.first << ' ' << j << '\n';
      }
    }
  }

private:
  std::map<Date, std::set<std::string>> records_;
};


int main() {
  Database db;
  std::string command;
  try {
    while (getline(std::cin, command)) {
      std::stringstream commandStream(command);
      std::string op;
      commandStream >> op;
      if (op.empty()) {
        continue;
      }
      if (op == "Add") {
        std::string dateStr, event;
        commandStream >> dateStr >> event;
        Date date(dateStr);
        db.AddEvent(date, event);

      } else if (op == "Del") {
        std::string dateStr, event;
        commandStream >> dateStr >> event;
        Date date(dateStr);
        if (event.empty()) {
          std::cout << "Deleted " << db.DeleteDate(date) << " events" << '\n';
        } else {
          if (db.DeleteEvent(date, event)) {
            std::cout << "Deleted successfully" << '\n';
          } else {
            std::cout << "Event not found" << '\n';
          }
        }

      } else if (op == "Find") {
        std::string dateStr;
        commandStream >> dateStr;
        Date date(dateStr);
        std::set<std::string> events = db.Find(date);
        for (const auto& i : events) {
          std::cout << i << '\n';
        }

      } else if (op == "Print") {
        db.Print();

      } else {
        throw std::runtime_error("Unknown command: " + op);
      }
    }
  } catch (std::exception& ex) {
    std::cout << ex.what();
  }
  return 0;
}
