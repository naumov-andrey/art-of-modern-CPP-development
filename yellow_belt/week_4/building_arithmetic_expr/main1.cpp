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

string BuildExpression(int x, const vector<operation_t>& operations) {
  string expr = to_string(x);
  for_each(operations.begin(), operations.end(), [&expr](const operation_t& op) mutable {
    expr.append(") " + string(1, op.type) + " " + to_string(op.value));
  });
  string temp(operations.size(), '(');
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
