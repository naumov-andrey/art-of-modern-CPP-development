#include <iomanip>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <utility>

using namespace std;

class ReadingManager {
public:
  ReadingManager():
    user_page_counts_(MAX_USER_COUNT_, 0),
    page_count_rating_(MAX_PAGE_COUNT_, 0),
    user_count_(0)
  {}

  void Read(int user_id, int page_count) {
    if (user_page_counts_[user_id - 1] == 0) {
      ++user_count_;
      for_each(next(page_count_rating_.begin(), page_count), page_count_rating_.end(), [](int& r) {
        ++r;
      });
    } else {
      for_each(next(page_count_rating_.begin(), user_page_counts_[user_id - 1]),
               next(page_count_rating_.begin(), page_count),
               [](int& r) {
        --r;
      });
    }
    user_page_counts_[user_id - 1] = page_count;
  }

  double Cheer(int user_id) const {
    if (user_page_counts_[user_id - 1] == 0) {
      return 0;
    }
    if (user_count_ == 1) {
      return 1;
    }
    return page_count_rating_[user_page_counts_[user_id - 1] - 1] * 1.0 / (user_count_ - 1);
  }

private:
  static const int MAX_USER_COUNT_ = 100'000;
  static const int MAX_PAGE_COUNT_ = 1'000;

  vector<int> user_page_counts_;
  vector<int> page_count_rating_;
  int user_count_;
};


int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ReadingManager manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int user_id;
    cin >> user_id;

    if (query_type == "READ") {
      int page_count;
      cin >> page_count;
      manager.Read(user_id, page_count);
    } else if (query_type == "CHEER") {
      cout << setprecision(6) << manager.Cheer(user_id) << "\n";
    }
  }

  return 0;
}
