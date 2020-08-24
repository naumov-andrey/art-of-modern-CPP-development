#include <string>
#include <vector>
#include <list>
#include "test_runner.h"
using namespace std;

class Editor {
public:
  Editor():
    tokens_(),
    buffer_(),
    cursor_(tokens_.begin())
  {}

  void Left() { cursor_ = Prev(cursor_);}

  void Right() { cursor_ = Next(cursor_);}

  void Insert(char token) { tokens_.insert(cursor_, token);}

  void Cut(size_t tokens = 1) {
    Copy(tokens);
    cursor_ = tokens_.erase(cursor_, Next(cursor_, tokens));
  }

  void Copy(size_t tokens = 1) {
    buffer_.assign(cursor_, Next(cursor_, tokens));
  }

  void Paste() {
    tokens_.insert(cursor_, buffer_.begin(), buffer_.end());
  }

  string GetText() const { return {tokens_.begin(), tokens_.end()};}

private:
  list<char> tokens_;
  list<char> buffer_;
  list<char>::iterator cursor_;

  list<char>::iterator Next(list<char>::iterator it, size_t n = 1) const {
    while (n != 0) {
      if (it == tokens_.end()) {
        break;
      }
      ++it;
      --n;
    }
    return it;
  }

  list<char>::iterator Prev(list<char>::iterator it, size_t n = 1) const {
    while (n != 0) {
      if (it == tokens_.begin()) {
        break;
      }
      --it;
      --n;
    }
    return it;
  }
};

void TypeText(Editor& editor, const string& text) {
  for(char c : text) {
    editor.Insert(c);
  }
}

void TestEditing() {
  {
    Editor editor;

    const size_t text_len = 12;
    const size_t first_part_len = 7;
    TypeText(editor, "hello, world");
    for(size_t i = 0; i < text_len; ++i) {
      editor.Left();
    }
    editor.Cut(first_part_len);
    for(size_t i = 0; i < text_len - first_part_len; ++i) {
      editor.Right();
    }
    TypeText(editor, ", ");
    editor.Paste();
    editor.Left();
    editor.Left();
    editor.Cut(3);

    ASSERT_EQUAL(editor.GetText(), "world, hello");
  }
  {
    Editor editor;

    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Right();
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "misprint");
  }
}

void TestReverse() {
  Editor editor;

  const string text = "esreveR";
  for(char c : text) {
    editor.Insert(c);
    editor.Left();
  }

  ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
  Editor editor;
  ASSERT_EQUAL(editor.GetText(), "");

  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
  Editor editor;

  editor.Paste();
  TypeText(editor, "example");
  editor.Left();
  editor.Left();
  editor.Paste();
  editor.Right();
  editor.Paste();
  editor.Copy(0);
  editor.Paste();
  editor.Left();
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestEditing);
  RUN_TEST(tr, TestReverse);
  RUN_TEST(tr, TestNoText);
  RUN_TEST(tr, TestEmptyBuffer);
  return 0;
}
