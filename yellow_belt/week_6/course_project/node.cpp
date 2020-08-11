#include "node.h"

bool EmptyNode::Evaluate(const Date& date, const string& event) {
  return true;
}


LogicalOperationNode::LogicalOperationNode(
  LogicalOperation logical_operation,
  shared_ptr<Node> left,
  shared_ptr<Node> right):
    left_(left),
    right_(right),
    logical_operation_(logical_operation)
{}

bool LogicalOperationNode::Evaluate(const Date& date, const string& event) {
  switch (logical_operation_) {
    case LogicalOperation::Or:
      return left_->Evaluate(date, event) || right_->Evaluate(date, event);
    case LogicalOperation::And:
      return left_->Evaluate(date, event) && right_->Evaluate(date, event);
  }
}


DateComparisonNode::DateComparisonNode(Comparison cmp, const Date& date):
  ComparisonNode<Date>(cmp, date)
{}

bool DateComparisonNode::Evaluate(const Date& date, const string& event) {
  return Compare(date);
}


EventComparisonNode::EventComparisonNode(Comparison cmp, const string& event):
  ComparisonNode<string>(cmp, event)
{}

bool EventComparisonNode::Evaluate(const Date& date, const string& event) {
  return Compare(event);
}
