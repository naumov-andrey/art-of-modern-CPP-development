#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector<string> SplitIntoWords(const string& s) {
  vector<string> words;
  auto word_begin = begin(s);
  auto word_end = find(begin(s), end(s), ' ');
  words.emplace_back(word_begin, word_end);
  while (word_end != end(s)) {
    word_begin = ++word_end;
    word_end = find(word_end, end(s), ' ');
    words.emplace_back(word_begin, word_end);
  }
  return words;
}

int main() {
  string s = "C Cpp Java Python";

  vector<string> words = SplitIntoWords(s);
  cout << words.size() << " ";
  for (auto it = begin(words); it != end(words); ++it) {
    if (it != begin(words)) {
      cout << "/";
    }
    cout << *it;
  }
  cout << endl;

  return 0;
}
