#include "date.h"

#include <iomanip>

Date::Date(int year, int month, int day):
  year_(year),
  month_(month),
  day_(day)
{
  if (year_ < 0 || year_ > 9999) {
    throw std::invalid_argument("Year value is invalid: " + std::to_string(year_));
  }
  if (month_ < 1 || month_ > 12) {
    throw std::invalid_argument("Month value is invalid: " + std::to_string(month_));
  }
  if (day_ < 1 || day_ > 31) {
    throw std::invalid_argument("Day value is invalid: " + std::to_string(day_));
  }
}

int Date::GetYear() const { return year_;}

int Date::GetMonth() const { return month_;}

int Date::GetDay() const { return day_;}


ostream& operator << (ostream& os, const Date& d) {
  os << setw(4) << setfill('0') << d.GetYear()
     << '-'
     << setw(2) << setfill('0') << d.GetMonth()
     << '-'
     << setw(2) << setfill('0') << d.GetDay();
  return os;
}

bool operator == (const Date& lhs, const Date& rhs) {
  return (lhs.GetYear() == rhs.GetYear())
    && (lhs.GetMonth() == rhs.GetMonth())
    && (lhs.GetDay() == rhs.GetDay());
}

bool operator != (const Date& lhs, const Date& rhs) {
  return !(lhs == rhs);
}

bool operator < (const Date& lhs, const Date& rhs) {
  if (lhs.GetYear() == rhs.GetYear()) {
    if (lhs.GetMonth() == rhs.GetMonth()) {
      return lhs.GetDay() < rhs.GetDay();
    }
    return lhs.GetMonth() < rhs.GetMonth();
  }
  return lhs.GetYear() < rhs.GetYear();
}

bool operator > (const Date& lhs, const Date& rhs) {
  return rhs < lhs;
}

bool operator <= (const Date& lhs, const Date& rhs) {
  return (lhs < rhs) || (lhs == rhs);
}

bool operator >= (const Date& lhs, const Date& rhs) {
  return (lhs > rhs) || (lhs == rhs);
}

Date ParseDate(istream& is) {
  string date;
  is >> date;
  stringstream string_stream(date);
  bool ok = true;

  int year;
  ok = ok && (string_stream >> year);
  ok = ok && (string_stream.peek() == '-');
  string_stream.ignore(1);

  int month;
  ok = ok && (string_stream >> month);
  ok = ok && (string_stream.peek() == '-');
  string_stream.ignore(1);

  int day;
  ok = ok && (string_stream >> day);
  ok = ok && string_stream.eof();

  if (!ok) {
    throw logic_error("Wrong date format: " + date);
  }
  return Date(year, month, day);
}
