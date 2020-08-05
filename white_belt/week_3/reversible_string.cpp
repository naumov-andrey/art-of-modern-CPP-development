#include <string>

class ReversibleString {
public:
  ReversibleString() = default;

  ReversibleString(const std::string& str):
  str_(str)
  {}

  void Reverse()
  {
    for (size_t i = 0; i < str_.size() / 2; ++i) {
      char temp = str_[i];
      str_[i] = str_[str_.size() - 1 - i];
      str_[str_.size() - 1 - i] = temp;
    }
  }

  std::string ToString() const
  {
    return str_;
  }

private:
  std::string str_;
};
