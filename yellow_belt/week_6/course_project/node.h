#pragma once

#include "date.h"

#include <memory>

class Node {
public:
  virtual bool Evaluate(const Date& date, const string& event) = 0;
};


class EmptyNode: public Node {
public:
  bool Evaluate(const Date& date, const string& event) override;
};


enum class LogicalOperation {
  Or,
  And
};

class LogicalOperationNode: public Node {
public:
  LogicalOperationNode(LogicalOperation logical_operation, shared_ptr<Node> left, shared_ptr<Node> right);

  bool Evaluate(const Date& date, const string& event) override;

private:
  const shared_ptr<Node> left_, right_;
  const LogicalOperation logical_operation_;
};


enum class Comparison {
  Less,
  LessOrEqual,
  Greater,
  GreaterOrEqual,
  Equal,
  NotEqual
};

template <typename T>
class ComparisonNode: public Node {
public:
  ComparisonNode(Comparison cmp, const T& value):
    cmp_(cmp),
    value_(value)
  {}

  bool Compare(const T& t) {
    switch (cmp_) {
      case Comparison::Less:
        return t < value_;
      case Comparison::LessOrEqual:
        return t <= value_;
      case Comparison::Greater:
        return t > value_;
      case Comparison::GreaterOrEqual:
        return t >= value_;
      case Comparison::Equal:
        return t == value_;
      case Comparison::NotEqual:
        return t != value_;
    }
  }

private:
  const Comparison cmp_;
  const T value_;
};


class DateComparisonNode: public ComparisonNode<Date> {
public:
  DateComparisonNode(Comparison cmp, const Date& date);

  bool Evaluate(const Date& date, const string& event) override;
};


class EventComparisonNode: public ComparisonNode<string> {
public:
  EventComparisonNode(Comparison cmp, const string& event);

  bool Evaluate(const Date& date, const string& event) override;
};
