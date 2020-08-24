#include "stats.h"
#include <algorithm>
using namespace std;

Stats::Stats() {
  for (const auto& i : supported_methods_) {
    method_stats_[i] = 0;
  }
  for (const auto& i : supported_uri_) {
    uri_stats_[i] = 0;
  }
}

void Stats::AddMethod(string_view method) {
  auto it = find(supported_methods_.begin(), supported_methods_.end(), string(method));
  ++method_stats_[it == supported_methods_.end() ? supported_methods_.back() : *it];
}

void Stats::AddUri(string_view uri) {
  auto it = find(supported_uri_.begin(), supported_uri_.end(), string(uri));
  ++uri_stats_[it == supported_uri_.end() ? supported_uri_.back() : *it];
}

const map<string_view, int> & Stats::GetMethodStats() const { return method_stats_;}

const map<string_view, int> & Stats::GetUriStats() const { return uri_stats_;}

HttpRequest ParseRequest(string_view line) {
  array<string_view, 3> data;
  size_t pos = 0;
  while (line[pos] == ' ') {
    ++pos;
  }
  for (int i = 0; i < 3; ++i) {
    size_t space = line.find(' ', pos);
    data[i] = line.substr(pos, space - pos);
    pos = space + 1;
  }
  return {data[0], data[1], data[2]};
}
