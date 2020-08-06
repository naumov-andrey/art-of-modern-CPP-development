#include <iostream>
#include <map>
#include <string>

template<typename K, typename V>
V& GetRefStrict(std::map<K, V>& m, const K& key) {
  if (m.count(key) != 0) {
    return m[key];
  }
  throw std::runtime_error("No such key in map");
}

int main() {
  std::map<int, std::string> m = {{0, "value"}};
  std::string& item = GetRefStrict(m, 0);
  item = "newvalue";
  std::cout << m[0] << std::endl;
  return 0;
}
