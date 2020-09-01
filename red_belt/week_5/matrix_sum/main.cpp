#include "test_runner.h"
#include <vector>
#include <future>
#include <numeric>
using namespace std;

template <typename Iterator>
class Page {
public:
  Page(Iterator begin, Iterator end):
    begin_(begin),
    end_(end)
  {}

  Iterator begin() const { return begin_;}
  Iterator end() const { return end_;}

  size_t size() const { return distance(begin_, end_);}

private:
  Iterator begin_, end_;
};


template <typename Iterator>
class Paginator {
public:
  Paginator(Iterator begin, Iterator end, size_t page_size) {
    size_t page_count = 0;
    auto it = begin;
    while (distance(begin, end) > page_count++ * page_size) {
      pages_.emplace_back(it, (distance(it, end) <= page_size) ? end : next(it, page_size));
      it = next(it, page_size);
    }
  }

  auto begin() const { return pages_.begin();}
  auto end() const { return pages_.end();}

  size_t size() const { return pages_.size();}

private:
  vector<Page<Iterator>> pages_;
};


template <typename C>
auto Paginate(C& c, size_t page_size) {
  return Paginator(c.begin(), c.end(), page_size);
}

template <typename ContainerOfVector>
int64_t SumSingleThread(const ContainerOfVector& matrix) {
  int64_t sum = 0;
  for (const auto& row : matrix) {
    for (auto value : row) {
      sum += value;
    }
  }
  return sum;
}

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
  const int CORES = 4;
  size_t page_size;
  if (matrix.size() < CORES) {
    page_size = matrix.size();
  } else {
    page_size = matrix.size() / CORES + 1;
  }
  vector<future<int64_t>> row_sums;
  for (const auto& part : Paginate(matrix, page_size)) {
    row_sums.push_back(async([part]() {
      return SumSingleThread(part);
    }));
  }
  int64_t sum = 0;
  for (auto& i : row_sums) {
    sum += i.get();
  }
  return sum;
}

void TestCalculateMatrixSum() {
  const vector<vector<int>> matrix = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
  };
  ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);

  const vector<vector<int>> matrix2 = {
    {1, 1, 1},
    {1, 1, 1},
    {1, 1, 1}
  };
  ASSERT_EQUAL(CalculateMatrixSum(matrix2), 9);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestCalculateMatrixSum);
}