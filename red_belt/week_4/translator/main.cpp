#include "test_runner.h"
#include <string>
#include <deque>
#include <algorithm>

using namespace std;

class Translator {
public:
  void Add(string_view source, string_view target) {
    string_view s = GetStringView(source);
    string_view t = GetStringView(target);
    forward_[s] = t;
    backward_[t] = s;
  }

  string_view TranslateForward(string_view source) const {
    return Translate(forward_, source);
  }

  string_view TranslateBackward(string_view target) const {
    return Translate(backward_, target);
  }

private:
  deque<string> words_;
  map<string_view, string_view> forward_;
  map<string_view, string_view> backward_;

  string_view Translate(const map<string_view, string_view>& dict, string_view word) const {
    auto it = dict.find(word);
    return it == dict.end() ? string_view() : it->second;
  }

  string_view GetStringView(string_view str) {
    for (const auto* i : {&forward_, &backward_}) {
      auto it = i->find(str);
      if (it != i->end()) {
        return it->first;
      }
    }
    return words_.emplace_back(str);
  }
};

void TestSimple() {
  Translator translator;
  translator.Add(string("okno"), string("window"));
  translator.Add(string("stol"), string("table"));

  ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
  ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
  ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSimple);
  return 0;
}
