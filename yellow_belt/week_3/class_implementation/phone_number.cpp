#include "phone_number.h"

#include <stdexcept>
#include <exception>
#include <sstream>

PhoneNumber::PhoneNumber(const string &international_number) {
  if (international_number.empty()) {
    throw invalid_argument("Empty number");
  }
  if (international_number[0] != '+') {
    throw invalid_argument("No '+'");
  }
  int first_hyphen_pos = international_number.find('-');
  if (first_hyphen_pos == string::npos) {
    throw invalid_argument("No city code");
  }
  country_code_ = international_number.substr(1, first_hyphen_pos - 1);
  int second_hyphen_pos = international_number.find('-', first_hyphen_pos + 1);
  if (second_hyphen_pos == string::npos || second_hyphen_pos == international_number.size() - 1) {
    throw invalid_argument("No local number");
  }
  city_code_ = international_number.substr(first_hyphen_pos + 1,second_hyphen_pos - first_hyphen_pos - 1);
  local_number_ = international_number.substr(second_hyphen_pos + 1);
}

string PhoneNumber::GetCountryCode() const {
  return country_code_;
}

string PhoneNumber::GetCityCode() const {
  return city_code_;
}

string PhoneNumber::GetLocalNumber() const {
  return local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
  stringstream international_number;
  international_number << '+' << country_code_ << '-' << city_code_ << '-' << local_number_;
  return international_number.str();
}
