#include <vector>
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
