#include "test_runner.h"

#include <vector>

using namespace std;

template <typename Token>
using Sentence = vector<Token>;


template <typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens) {
  vector<Sentence<Token>> result;
  auto it = tokens.begin();
  Sentence<Token> sentence;
  while (it != tokens.end()) {
    while (it != tokens.end() && !it->IsEndSentencePunctuation()) {
      sentence.emplace_back(move(*(it++)));
    }
    while (it != tokens.end() && it->IsEndSentencePunctuation()) {
      sentence.emplace_back(move(*(it++)));
    }
    result.emplace_back(move(sentence));
  }
  return result;
}


struct TestToken {
  string data;
  bool is_end_sentence_punctuation = false;

  bool IsEndSentencePunctuation() const {
    return is_end_sentence_punctuation;
  }
  bool operator==(const TestToken& other) const {
    return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
  }
};

ostream& operator<<(ostream& stream, const TestToken& token) {
  return stream << token.data;
}

void TestSplitting() {
  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!"}})),
    vector<Sentence<TestToken>>({
                                  {{"Split"}, {"into"}, {"sentences"}, {"!"}}
                                })
  );

  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}})),
    vector<Sentence<TestToken>>({
                                  {{"Split"}, {"into"}, {"sentences"}, {"!", true}}
                                })
  );

  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true}})),
    vector<Sentence<TestToken>>({
                                  {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
                                  {{"Without"}, {"copies"}, {".", true}},
                                })
  );
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSplitting);
  return 0;
}
