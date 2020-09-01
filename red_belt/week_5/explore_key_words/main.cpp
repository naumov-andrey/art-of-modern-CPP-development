#include "test_runner.h"
#include "profile.h"

#include <map>
#include <string>
#include <functional>
#include <future>
using namespace std;


template <typename Iterator>
class Page {
public:
  Page(Iterator begin, Iterator end):
    begin_(begin),
    end_(end)
  {}

  Iterator begin() const { return begin_;}
  Iterator end() const { return end_;}

  size_t size() const { return distance(begin_, end_);}

private:
  Iterator begin_, end_;
};

template <typename Iterator>
class Paginator {
public:
  Paginator(Iterator begin, Iterator end, size_t page_size) {
    size_t page_count = 0;
    auto it = begin;
    while (distance(begin, end) > page_count++ * page_size) {
      pages_.emplace_back(it, (distance(it, end) <= page_size) ? end : next(it, page_size));
      it = next(it, page_size);
    }
  }

  auto begin() const { return pages_.begin();}
  auto end() const { return pages_.end();}

  size_t size() const { return pages_.size();}

private:
  vector<Page<Iterator>> pages_;
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
  return Paginator(c.begin(), c.end(), page_size);
}


vector<string> ReadString(istream& input) {
  vector<string> strings;
  for (string line; getline(input, line); ) {
    strings.push_back(move(line));
  }
  return strings;
}


struct Stats {
  map<string, int> word_frequences;

  void operator += (const Stats& other) {
    for (const auto& i : other.word_frequences) {
      word_frequences[i.first] += i.second;
    }
  }
};

Stats ExploreLine(const set<string>& key_words, const string& line) {
  Stats stats;
  if (!line.empty()) {
    size_t pos = 0;
    while (pos != string::npos) {
      size_t ws = line.find(' ', pos);
      if (key_words.count(line.substr(pos, ws - pos)) > 0) {
        ++stats.word_frequences[line.substr(pos, ws - pos)];
      }
      pos = ws == string::npos ? ws : ws + 1;
    }
  }
  return stats;
}

Stats ExploreKeyWordsSingleThread(const set<string>& key_words, const Page<vector<string>::iterator>& input) {
  Stats result;
  for (const auto& line : input) {
    result += ExploreLine(key_words, line);
  }
  return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
  const int CORES = 4;
  vector<string> lines = ReadString(input);
  size_t  page_size = lines.size() < CORES ? lines.size() : lines.size() / CORES + 1;
  vector<future<Stats>> stats;
  stats.reserve(CORES);
  auto paginator = Paginate(lines, page_size);
  for (const auto& i : paginator) {
    stats.push_back(async(ExploreKeyWordsSingleThread, ref(key_words), ref(i)));
  }
  Stats result;
  for (auto& i : stats) {
    result += i.get();
  }
  return result;
}


void TestBasic() {
  const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

  stringstream ss;
  ss << "this new yangle service really rocks\n";
  ss << "It sucks when yangle isn't available\n";
  ss << "10 reasons why yangle is the best IT company\n";
  ss << "yangle rocks others suck\n";
  ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

  const auto stats = ExploreKeyWords(key_words, ss);
  const map<string, int> expected = {
    {"yangle", 6},
    {"rocks", 2},
    {"sucks", 1}
  };
  ASSERT_EQUAL(stats.word_frequences, expected);
}

void TestLittle() { LOG_DURATION("TestBasic")
  const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

  stringstream ss;
  ss << "yangle really rocks\n";

  const auto stats = ExploreKeyWords(key_words, ss);
  const map<string, int> expected = {
    {"yangle", 1},
    {"rocks", 1}
  };
  ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestBasic);
  RUN_TEST(tr, TestLittle);
  return 0;
}
