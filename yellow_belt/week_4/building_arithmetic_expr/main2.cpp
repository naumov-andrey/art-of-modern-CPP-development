#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

struct operation_t {
  char type;
  int value;
};

operation_t ParseOperation(const string& str) {
  stringstream string_stream(str);
  char op;
  int value;
  string_stream >> op >> value;
  return {op, value};
}

void AddOperationToExpression(string& expr, const operation_t& op, int& count_of_brackets, bool& is_high_priority) {
  if (op.type == '*' || op.type == '/') {
    if (is_high_priority) {
      expr.append(" " + string(1, op.type) + " " + to_string(op.value));
    } else {
      expr.append(") " + string(1, op.type) + " " + to_string(op.value));
      is_high_priority = true;
      ++count_of_brackets;
    }
  } else {
    is_high_priority = false;
    expr.append(" " + string(1, op.type) + " " + to_string(op.value));
  }
}

string BuildExpression(int x, const vector<operation_t>& operations) {
  string expr = to_string(x);
  int count_of_brackets = 0;
  bool is_high_priority = true;
  for_each(operations.begin(), operations.end(), [&expr, &count_of_brackets, &is_high_priority](const operation_t& op) mutable {
    AddOperationToExpression(expr, op, count_of_brackets, is_high_priority);
  });
  string temp(count_of_brackets, '(');
  return temp + expr;
}

int main() {
  string line;
  getline(cin, line);
  int x = stoi(line);
  getline(cin, line);
  int n = stoi(line);
  vector<operation_t> operations(n);
  for (int i = 0; i < n; ++i) {
    getline(cin, line);
    operations[i] = ParseOperation(line);
  }
  cout << BuildExpression(x, operations);
  return 0;
}
