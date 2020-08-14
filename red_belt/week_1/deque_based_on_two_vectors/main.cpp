#include "deque.h"
#include "test_runner.h"
using namespace std;

void TestDeque() {
  Deque<int> d;
  ASSERT(d.Empty());
  ASSERT_EQUAL(d.Size(), 0u);
  d.PushBack(2);
  ASSERT(!d.Empty());
  ASSERT_EQUAL(d.Back(), 2u);
  ASSERT_EQUAL(d.Front(), 2u);
  d.PushBack(3);
  d.PushFront(1);
  ASSERT_EQUAL(d.Back(), 3u);
  ASSERT_EQUAL(d.Front(), 1u);
  ASSERT(!d.Empty());
  ASSERT_EQUAL(d.Size(), 3u);
  ASSERT_EQUAL(d.Front(), 1u);
  ASSERT_EQUAL(d.Back(), 3u);
  try {
    d.At(3);
    ASSERT(false);
  } catch (out_of_range&) {}
  ASSERT_EQUAL(d[0], 1u);
  ASSERT_EQUAL(d[1], 2u);
  ASSERT_EQUAL(d[2], 3u);

  Deque<int> d1;
  d1.PushFront(2);
  d1.PushFront(1);
  d1.PushBack(3);
  d1.PushBack(4);
  AssertEqual(d1[0], 1);
  AssertEqual(d1[1], 2);
  AssertEqual(d1[2], 3);
  AssertEqual(d1[3], 4);
  AssertEqual(d1.At(0), 1);
  AssertEqual(d1.At(1), 2);
  AssertEqual(d1.At(2), 3);
  AssertEqual(d1.At(3), 4);
  try {
    d1.At(4);
    ASSERT(false);
  } catch (out_of_range&) {}
  d1.PushBack(5);
  AssertEqual(d1[4], 5);

  Deque<int> d2;
  d2.PushFront(1);
  ASSERT(!d2.Empty());
  d2.PushFront(2);
  d2.PushFront(3);
  ASSERT_EQUAL(d2.Back(), 1u);
  ASSERT_EQUAL(d2.Front(), 3u);

  Deque<int> d3;
  d3.PushBack(1);
  d3.PushBack(2);
  d3.PushBack(3);
  ASSERT_EQUAL(d3.Back(), 3u);
  ASSERT_EQUAL(d3.Front(), 1u);
  d3[0] = 4;
  d3[1] = 5;
  d3[2] = 6;
  AssertEqual(d3[0], 4);
  AssertEqual(d3[1], 5);
  AssertEqual(d3[2], 6);
  d3.At(0) = 7;
  d3.At(1) = 8;
  d3.At(2) = 9;
  AssertEqual(d3[0], 7);
  AssertEqual(d3[1], 8);
  AssertEqual(d3[2], 9);
  AssertEqual(d3[0], d3.At(0));
  AssertEqual(d3[1], d3.At(1));
  AssertEqual(d3[2], d3.At(2));
  d3.Front() = 1;
  d3.Back() = 3;
  AssertEqual(d3.Front(), 1);
  AssertEqual(d3.Back(), 3);

  Deque<int> d4;
  d4.PushFront(1);
  d4.PushBack(2);
  d4[0] = d4[1];
  int a = d4.At(0);
  int& b = d4.At(1);
  a = 3;
  b = 3;
  AssertEqual(d4[0], 2);
  AssertEqual(d4[1], 3);
}


int main() {
  TestRunner tr;
  RUN_TEST(tr, TestDeque);
  return 0;
}
