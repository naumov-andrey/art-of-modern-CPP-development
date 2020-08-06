#include <iostream>
#include <vector>
#include <map>
#include <utility>

template<typename T>
T Sqr(const T& x);

template<typename T>
std::vector<T> Sqr(const std::vector<T>& v);

template<typename Key, typename Value>
std::map<Key, Value> Sqr(const std::map<Key, Value>& m);

template<typename First, typename Second>
std::pair<First, Second> Sqr(const std::pair<First, Second>& p);

template<typename T>
T Sqr(const T& x) {
  return x * x;
}

template<typename T>
std::vector<T> Sqr(const std::vector<T>& v) {
  std::vector<T> v_squared;
  v_squared.reserve(v.size());
  for (size_t i = 0; i < v.size(); ++i) {
    v_squared.push_back(Sqr(v[i]));
  }
  return v_squared;
}

template<typename Key, typename Value>
std::map<Key, Value> Sqr(const std::map<Key, Value>& m) {
  std::map<Key, Value> m_squared;
  for (auto& i : m) {
    m_squared[i.first] = Sqr(i.second);
  }
  return m_squared;
}

template<typename First, typename Second>
std::pair<First, Second> Sqr(const std::pair<First, Second>& p) {
  std::pair<First, Second> p_squared;
  p_squared.first = Sqr(p.first);
  p_squared.second = Sqr(p.second);
  return p_squared;
}

using namespace std;

int main() {
  vector<int> v = {1, 2, 3};
  cout << "vector:";
  for (int x : Sqr(v)) {
    cout << ' ' << x;
  }
  cout << endl;

  map<int, pair<int, int>> map_of_pairs = {
      {4, {2, 2}},
      {7, {4, 3}}
  };
  cout << "map of pairs:" << endl;
  for (const auto& x : Sqr(map_of_pairs)) {
    cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
  }
  return 0;
}
