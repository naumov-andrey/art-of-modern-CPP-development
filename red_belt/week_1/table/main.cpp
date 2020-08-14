#include "test_runner.h"
#include "table.cpp"

using namespace std;

void TestTable() {
  Table<int> t(1, 1);
  ASSERT_EQUAL(t.Size().first, 1u);
  ASSERT_EQUAL(t.Size().second, 1u);
  t[0][0] = 42;
  ASSERT_EQUAL(t[0][0], 42);
  t.Resize(3, 4);
  ASSERT_EQUAL(t.Size().first, 3u);
  ASSERT_EQUAL(t.Size().second, 4u);

  Table<int> t2(0, 3);
  ASSERT_EQUAL(t2.Size().first, 0u);
  ASSERT_EQUAL(t2.Size().second, 0u);

  Table<int> t3(3, 0);
  ASSERT_EQUAL(t3.Size().first, 0u);
  ASSERT_EQUAL(t3.Size().second, 0u);
  t3.Resize(1, 2);
  ASSERT_EQUAL(t3[0][1], 0u);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestTable);
  return 0;
}