#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <deque>
#include <map>
#include <string>
using namespace std;

class InvertedIndex {
public:
  void Add(string document);
  vector<pair<size_t, size_t>> Lookup(const string& word) const;


  size_t GetDocsCount() const { return docs_count_;}

private:
  size_t docs_count_ = 0;
  map<string, vector<pair<size_t, size_t>>> index_;
};

class SearchServer {
public:
  SearchServer() = default;
  explicit SearchServer(istream& document_input);
  void UpdateDocumentBase(istream& document_input);
  void AddQueriesStream(istream& query_input, ostream& search_results_output);

private:
  InvertedIndex index_;
};
