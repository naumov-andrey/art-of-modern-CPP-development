#pragma once

#include <cstdlib>
#include <algorithm>

template <typename T>
class SimpleVector {
public:
  SimpleVector():
    begin_(nullptr),
    size_(0),
    capacity_(0)
  {}

  explicit SimpleVector(size_t size):
    begin_(new T[size]),
    size_(size),
    capacity_(size)
  {}

  ~SimpleVector() { delete [] begin_;}

  T& operator [] (size_t index) { return begin_[index];}

  void operator = (const SimpleVector& other) {
    delete [] begin_;
    begin_ = new T[other.capacity_];
    std::copy(other.begin(), other.end(), begin_);
    size_ = other.size_;
    capacity_ = other.capacity_;
  }

  T* begin() { return begin_;}
  const T* begin() const { return begin_;}
  T* end() { return begin_ + size_;}
  const T* end() const { return begin_ + size_;}

  size_t Size() const { return size_;}
  size_t Capacity() const { return capacity_;}

  void PushBack(const T& value) {
    if (Size() == Capacity()) {
      capacity_ = Capacity() == 0 ? 1 : 2 * Capacity();
      T* new_begin = new T[capacity_];
      for (size_t i = 0; i < Size(); ++i) {
        new_begin[i] = begin_[i];
      }
      delete [] begin_;
      begin_ = new_begin;
    }
    begin_[size_++] = value;
  }

private:
  T* begin_;
  size_t size_;
  size_t capacity_;
};
