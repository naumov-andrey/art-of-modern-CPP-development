#pragma once

#include <cstdlib>

template <typename T>
class SimpleVector {
public:
  SimpleVector():
    begin_(nullptr),
    end_(nullptr),
    size_(0)
  {}

  explicit SimpleVector(size_t size):
    begin_(new T[size]),
    end_(begin_ + size),
    size_(size)
  {}

  ~SimpleVector() { delete [] begin_;}

  T& operator[](size_t index) { return begin_[index];}

  T* begin() { return begin_;}
  T* end() { return begin_ + size_;}

  size_t Size() const { return size_;}
  size_t Capacity() const { return end_ - begin_;}

  void PushBack(const T& value) {
    if (Size() == Capacity()) {
      size_t new_capacity = Capacity() == 0 ? 1 : 2 * Capacity();
      T* new_begin = new T[new_capacity];
      for (size_t i = 0; i < Size(); ++i) {
        new_begin[i] = begin_[i];
      }
      delete [] begin_;
      begin_ = new_begin;
      end_ = begin_ + new_capacity;
    }
    begin_[size_++] = value;
  }

private:
  T* begin_;
  T* end_;
  size_t size_;
};
