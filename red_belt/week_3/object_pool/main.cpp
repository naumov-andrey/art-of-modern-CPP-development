#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
  T* Allocate() {
    T* object;
    if (!free_.empty()) {
      object = free_.front();
      free_.pop();
    } else {
      object = new T();
    }
    allocated_.insert(object);
    return object;
  }

  T* TryAllocate() {
    T* object;
    if (!free_.empty()) {
      object = free_.front();
      allocated_.insert(object);
      free_.pop();
    } else {
      object = nullptr;
    }
    return object;
  }

  void Deallocate(T* object) {
    auto it = allocated_.find(object);
    if (it == allocated_.end()) {
      throw invalid_argument("No such object");
    }
    free_.push(*it);
    allocated_.erase(it);
  }

  ~ObjectPool() {
    for (auto i : allocated_) {
      delete i;
    }
    while (!free_.empty()) {
      delete free_.front();
      free_.pop();
    }
  }

private:
  set<T*> allocated_;
  queue<T*> free_;
};

void TestObjectPool() {
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}
