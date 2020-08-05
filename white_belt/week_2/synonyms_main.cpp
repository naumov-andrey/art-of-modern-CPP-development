#include <iostream>
#include <string>
#include <set>
#include <map>

int main10()
{
  size_t q;
  std::cin >> q;
  std::map<std::string, std::set<std::string>> synonyms;
  for (size_t i = 0; i < q; ++i) {
    std::string command;
    std::cin >> command;
    if (command == "ADD") {
      std::string word1, word2;
      std::cin >> word1 >> word2;
      synonyms[word1].insert(word2);
      synonyms[word2].insert(word1);
    } else if (command == "COUNT") {
      std::string word;
      std::cin >> word;
      std::cout << synonyms[word].size() << '\n';
    } else if (command == "CHECK") {
      std::string word1, word2;
      std::cin >> word1 >> word2;
      if (synonyms[word1].count(word2) > 0) {
        std::cout << "YES" << '\n';
      } else {
        std::cout << "NO" << '\n';
      }
    }
  }
  return 0;
}
