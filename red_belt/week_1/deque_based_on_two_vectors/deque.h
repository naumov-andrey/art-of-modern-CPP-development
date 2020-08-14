#pragma once

#include <vector>
#include <stdexcept>
using namespace std;

template <typename T>
class Deque {
public:
  Deque() = default;

  bool Empty() const { return front_.empty() && back_.empty();}
  size_t Size() const { return front_.size() + back_.size();}

  T& operator [] (size_t i) { return (i < front_.size()) ? front_[front_.size() - i - 1] : back_[i - front_.size()];}
  const T& operator [](size_t i) const { return (i < front_.size()) ? front_[front_.size() - i - 1] : back_[i - front_.size()];}

  T& At(size_t i) {
    ValidateIndex(i);
    return operator[](i);
  }

  const T& At(size_t i) const {
    ValidateIndex(i);
    return operator[](i);
  }

  T& Front() { return front_.empty() ? back_.front() : front_.back();}
  const T& Front() const { return front_.empty() ? back_.front() : front_.back();}

  T& Back() { return back_.empty() ? front_.front() : back_.back();}
  const T& Back() const { return back_.empty() ? front_.front() : back_.back();}

  void PushFront(const T& value) { front_.push_back(value);}
  void PushBack(const T& value) { back_.push_back(value);}

private:
  vector<T> front_, back_;

  void ValidateIndex(size_t index) {
    if (index >= Size()) {
      throw out_of_range("Validating index: out of range");
    }
  }
};
