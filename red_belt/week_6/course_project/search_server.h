#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <deque>
#include <map>
#include <string>
#include <future>
#include "synchronized.h"
using namespace std;

class InvertedIndex {
public:
  InvertedIndex() = default;
  InvertedIndex(istream& document_input);
  const vector<pair<size_t, size_t>>& Lookup(string_view word) const;

  size_t GetDocsCount() const { return docs_.size();}

private:
  deque<string> docs_;
  map<string_view, vector<pair<size_t, size_t>>> index_;
};

class SearchServer {
public:
  SearchServer() = default;

  explicit SearchServer(istream &document_input);

  void UpdateDocumentBase(istream &document_input);

  void AddQueriesStream(istream &query_input, ostream &search_results_output);

  void AddQueriesOneThread(istream &query_input, ostream &search_results_output);

private:
  Synchronized<InvertedIndex> index_;
  vector<future<void>> future_pool_;
};
