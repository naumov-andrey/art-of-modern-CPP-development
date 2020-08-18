#pragma once

#include <array>
#include <stdexcept>
using namespace std;

template <typename T, size_t N>
class StackVector {
public:
  explicit StackVector(size_t a_size = 0):
    size_(a_size)
  {
    if (a_size > N) {
      throw invalid_argument("Size greater then capacity");
    }
  }

  T& operator[](size_t index) { return array_[index];}
  const T& operator[](size_t index) const { return array_[index];}

  auto begin() { return array_.begin();}
  auto end() { return array_.begin() + size_;}
  auto begin() const { return array_.begin();}
  auto end() const { return array_.begin() + size_;}

  size_t Size() const { return size_;}
  size_t Capacity() const { return N;}

  void PushBack(const T& value) {
    if (size_ == N) {
      throw overflow_error("Push in full StackVector");
    }
    array_[size_++] = value;
  }

  T PopBack() {
    if (size_ == 0) {
      throw underflow_error("Pop from empty StackVector");
    }
    return array_[size_-- - 1];
  }

private:
  size_t size_;
  array<T, N> array_;
};
