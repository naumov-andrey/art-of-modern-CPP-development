#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include <deque>

using namespace std;

template <typename T>
class PriorityCollection {
public:
  using Id = size_t;

  Id Add(T object) {
    objects_.push_back(move(object));
    auto insert_result = priorities_.insert({0, cur_max_id_});
    ids_[cur_max_id_] = insert_result.first;
    return cur_max_id_++;
  }

  template <typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end, IdOutputIt ids_begin) {
    for (auto i = make_move_iterator(range_begin); i != make_move_iterator(range_end); ++i) {
      *(ids_begin++) = Add(*i);
    }
  }

  bool IsValid(Id id) const { return ids_.count(id) > 0;}

  const T& Get(Id id) const { return objects_[id];}

  void Promote(Id id) {
    auto it = ids_[id];
    pair<int, Id> priority_item = *it;
    priorities_.erase(it);
    ++priority_item.first;
    auto insert_result = priorities_.insert(priority_item);
    ids_[id] = insert_result.first;
  }

  pair<const T&, int> GetMax() const {
    auto rit = priorities_.rbegin();
    return {objects_[rit->second], rit->first};
  }

  pair<T, int> PopMax() {
    auto it = prev(priorities_.end());
    pair<int, Id> priority_item = *it;
    ids_.erase(it->second);
    priorities_.erase(it);
    return {move(objects_[priority_item.second]), priority_item.first};
  }

private:
  vector<T> objects_;
  set<pair<int, Id>> priorities_;
  map<Id, set<pair<int, Id>>::const_iterator> ids_;

  Id cur_max_id_ = 0;
};


class StringNonCopyable : public string {
public:
  using string::string;
  StringNonCopyable(const StringNonCopyable&) = delete;
  StringNonCopyable(StringNonCopyable&&) = default;
  StringNonCopyable& operator=(const StringNonCopyable&) = delete;
  StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
  PriorityCollection<StringNonCopyable> strings;
  const auto white_id = strings.Add("white");
  const auto yellow_id = strings.Add("yellow");
  const auto red_id = strings.Add("red");

  strings.Promote(yellow_id);
  for (int i = 0; i < 2; ++i) {
    strings.Promote(red_id);
  }
  strings.Promote(yellow_id);
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "red");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "yellow");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "white");
    ASSERT_EQUAL(item.second, 0);
  }
}

void TestIsValid() {
  PriorityCollection<int> integers;
  ASSERT(!integers.IsValid(PriorityCollection<int>::Id()));
  PriorityCollection<int>::Id id = integers.Add(1);
  auto get_result = integers.Get(id);
  ASSERT_EQUAL(get_result, 1);
  integers.PopMax();
  ASSERT(!integers.IsValid(id));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestNoCopy);
  RUN_TEST(tr, TestIsValid);
  return 0;
}
