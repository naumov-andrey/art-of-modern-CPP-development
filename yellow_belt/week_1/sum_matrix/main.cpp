#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
using namespace std;

class Matrix {
public:
  Matrix() {
    num_rows_ = 0;
    num_cols_ = 0;
  }
  Matrix(int num_rows, int num_cols) {
    ValidateSize(num_rows, num_cols);
    num_rows_ = num_rows;
    num_cols_ = num_cols;
    data_ = vector<vector<int>> (num_rows_, vector<int>(num_cols_, 0));
  }

  void Reset(int new_num_rows, int new_num_cols) {
    ValidateSize(new_num_rows, new_num_cols);
    data_.clear();
    num_rows_ = new_num_rows;
    num_cols_ = new_num_cols;
    data_ = vector<vector<int>> (num_rows_, vector<int>(num_cols_, 0));
  }

  int At(int row_num, int col_num) const {
    ValidateIndex(row_num, col_num);
    return data_[row_num][col_num];
  }

  int& At(int row_num, int col_num) {
    ValidateIndex(row_num, col_num);
    return data_[row_num][col_num];
  }

  bool IsEmpty() const {
    return (num_rows_ == 0 || num_cols_ == 0);
  }

  int GetNumRows() const { return num_rows_;}
  int GetNumColumns() const { return num_cols_;}

private:
  int num_rows_;
  int num_cols_;
  vector<vector<int>> data_;

  void ValidateIndex(int row_num, int col_num) const {
    if (row_num < 0 || row_num > num_rows_ - 1 || col_num < 0 || col_num > num_cols_ - 1) {
      throw out_of_range("Wrong index");
    }
  }

  void ValidateSize(int num_rows, int num_cols) const {
    if (num_rows < 0 || num_cols < 0) {
      throw out_of_range("Wrong size");
    }
  }
};

istream& operator>>(istream& in, Matrix& matrix) {
  int num_rows, num_cols;
  in >> num_rows >> num_cols;
  matrix.Reset(num_rows, num_cols);
  int temp;
  for (int i = 0; i < num_rows; ++i) {
    for (int j = 0; j < num_cols; ++j) {
      in >> temp;
      matrix.At(i, j) = temp;
    }
  }
  return in;
}

ostream& operator<<(ostream& out, const Matrix& matrix) {
  out << matrix.GetNumRows() << ' ' << matrix.GetNumColumns() << '\n';
  for (int i = 0; i < matrix.GetNumRows(); ++i) {
    for (int j = 0; j < matrix.GetNumColumns(); ++j) {
      out << matrix.At(i, j) << ' ';
    }
    out << '\n';
  }
  return out;
}

bool operator==(const Matrix& lhs, const Matrix& rhs) {
  if (lhs.GetNumRows() == rhs.GetNumRows() && lhs.GetNumColumns() == rhs.GetNumColumns()) {
    for (int i = 0; i < lhs.GetNumRows(); ++i) {
      for (int j = 0; j < lhs.GetNumColumns(); ++j) {
        if (lhs.At(i, j) != rhs.At(i, j)) {
          return false;
        }
      }
    }
    return true;
  } else if (lhs.IsEmpty() && rhs.IsEmpty()) {
    return true;
  }
  return false;
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs) {
  if (lhs.GetNumRows() == rhs.GetNumRows() && lhs.GetNumColumns() == rhs.GetNumColumns()) {
    Matrix matrix(lhs.GetNumRows(), lhs.GetNumColumns());
    for (int i = 0; i < lhs.GetNumRows(); ++i) {
      for (int j = 0; j < lhs.GetNumColumns(); ++j) {
        matrix.At(i, j) = lhs.At(i, j) + rhs.At(i, j);
      }
    }
    return matrix;
  } else if (lhs.IsEmpty() && rhs.IsEmpty()) {
    return Matrix();
  }
  throw invalid_argument("Matrix sizes are not equal");
}


int main() {
  Matrix m1(0,2), m2(0,3);
  cout << m1 + m2 << endl;
  return 0;
}
