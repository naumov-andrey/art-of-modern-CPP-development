#include <cstdint>
#include <algorithm>
#include <utility>

using namespace std;

template <typename T>
class SimpleVector {
public:
  SimpleVector():
    data_(nullptr),
    size_(0),
    capacity_(0)
  {}

  explicit SimpleVector(size_t size):
    data_(new T[size]),
    size_(size),
    capacity_(size)
  {}

  ~SimpleVector() {
    delete [] data_;
  }

  T& operator[](size_t index) { return data_[index];}

  T* begin() { return data_;}
  T* end() { return data_ + size_;}

  size_t Size() const { return size_;}
  size_t Capacity() const { return capacity_;}

  void PushBack(const T& value) {
    PushBackImpl(value);
  }

  void PushBack(T&& value) {
    PushBackImpl(move(value));
  }

private:
  T* data_;
  size_t size_;
  size_t capacity_;

  void PushBackImpl(T value) {
    if (size_ == capacity_) {
      capacity_ = capacity_ == 0 ? 1 : 2 * capacity_;
      T* new_data = new T[capacity_];
      move(data_, data_ + size_, new_data);
      delete [] data_;
      data_ = new_data;
    }
    data_[size_++] = T(move(value));
  }
};
