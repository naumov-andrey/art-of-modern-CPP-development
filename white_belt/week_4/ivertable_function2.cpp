#include <vector>
#include <algorithm>

class FunctionPart {
public:
  FunctionPart(char operation, double value) {
    operation_ = operation;
    value_ = value;
  }

  void Invert() {
    if (operation_ == '+') {
      operation_ = '-';
    } else if (operation_ == '-') {
      operation_ = '+';
    } else if (operation_ == '*') {
      operation_ = '/';
    } else {
      operation_ = '*';
    }
  }

  double Apply(double value) const {
    if (operation_ == '+') {
      return value + value_;
    } else if (operation_ == '-') {
      return value - value_;
    } else if (operation_ == '*') {
      return value * value_;
    }
    return value / value_;
  }

private:
  char operation_;
  double value_;
};

class Function {
public:
  Function() = default;

  void AddPart(char operation, double value) {
    parts_.emplace_back(operation, value);
  }

  void Invert() {
    for (auto& i : parts_) {
      i.Invert();
    }
    std::reverse(std::begin(parts_), std::end(parts_));
  }

  double Apply(double value) const {
    for (const auto& i : parts_) {
      value = i.Apply(value);
    }
    return value;
  }

private:
  std::vector<FunctionPart> parts_;
};
