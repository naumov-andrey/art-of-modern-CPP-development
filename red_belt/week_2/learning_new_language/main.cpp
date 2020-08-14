#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

class Learner {
public:
  int Learn(const vector<string>& words) {
    int newWords = 0;
    for (const auto& word : words) {
      if (dict_.insert(word).second) {
        ++newWords;
      }
    }
    return newWords;
  }

  vector<string> KnownWords() { return {dict_.begin(), dict_.end()};}

private:
  set<string> dict_;
};

int main() {
  Learner learner;
  string line;
  while (getline(cin, line)) {
    vector<string> words;
    stringstream ss(line);
    string word;
    while (ss >> word) {
      words.push_back(word);
    }
    cout << learner.Learn(words) << "\n";
  }
  cout << "=== known words ===\n";
  for (auto word : learner.KnownWords()) {
    cout << word << "\n";
  }
}
