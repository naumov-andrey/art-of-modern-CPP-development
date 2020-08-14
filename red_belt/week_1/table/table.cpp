#include <vector>
using namespace std;

template<typename T>
class Table {
public:
  Table(size_t row_count, size_t column_count):
    row_count_(row_count),
    column_count_(column_count),
    data_(row_count, vector<T>(column_count))
  {
    if (row_count_ == 0 || column_count_ == 0) {
      row_count_ = 0;
      column_count_ = 0;
      data_.clear();
    }
  }

  vector<T>& operator [] (size_t index) { return data_[index];}
  vector<T> operator [] (size_t index) const { return data_[index];}

  void Resize(size_t new_row_count, size_t new_column_count) {
    for (size_t i = 0; i < min(row_count_, new_row_count); ++i) {
      data_[i].resize(new_column_count);
    }
    column_count_ = new_column_count;

    data_.resize(new_row_count, vector<T>(new_column_count));
    row_count_ = new_row_count;
  }

  pair<size_t, size_t> Size() const { return make_pair(row_count_, column_count_);}

private:
  size_t row_count_, column_count_;
  vector<vector<T>> data_;
};
