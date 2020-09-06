#include "search_server.h"
#include "iterator_range.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <future>

vector<string_view> SplitIntoWords(string_view line) {
  vector<string_view> words;
  size_t first = 0;
  while (first < line.size())
  {
    const auto second = line.find_first_of(' ', first);
    if (first != second)
      words.emplace_back(line.substr(first, second-first));
    if (second == string_view::npos)
      break;
    first = second + 1;
  }
  return words;
}

SearchServer::SearchServer(istream& document_input):
  index_(document_input)
{}

void SearchServer::UpdateDocumentBase(istream& document_input) {
  InvertedIndex new_index(document_input);
  swap(index_.GetAccess().ref_to_value, new_index);
}

void SearchServer::AddQueriesStream(istream& query_input, ostream& search_results_output) {
  future_pool_.push_back(async(&SearchServer::AddQueriesOneThread, this, ref(query_input), ref(search_results_output)));
  if (future_pool_.size() == 6) {
    future_pool_.clear();
  }
}

void SearchServer::AddQueriesOneThread(istream& query_input, ostream& search_results_output) {
  vector<size_t> docids;
  vector<size_t> docid_count;
  for (string current_query; getline(query_input, current_query); ) {
    {
      auto access = index_.GetAccess();
      docid_count.assign(access.ref_to_value.GetDocsCount(), 0);

      for (const auto& word : SplitIntoWords(current_query)) {
        for (const auto&[docid, hit_count] : access.ref_to_value.Lookup(word)) {
          docid_count[docid] += hit_count;
        }
      }
    }

    docids.resize(docid_count.size());
    iota(docids.begin(), docids.end(), 0);
    partial_sort(
      docids.begin(),
      docids.begin() + min(5ul, docids.size()),
      docids.end(),
      [&](size_t lhs, size_t rhs) {
        return pair(docid_count[lhs], rhs) > pair(docid_count[rhs], lhs);
      }
    );

    search_results_output << current_query << ':';
    for (auto i : Head(docids, 5)) {
      if (docid_count[i] == 0) {
        break;
      }
      search_results_output << " {"
                            << "docid: " << i << ", "
                            << "hitcount: " << docid_count[i] << '}';
    }
    search_results_output << endl;
  }
}

InvertedIndex::InvertedIndex(istream &document_input) {
  for (string document; getline(document_input, document);) {
    docs_.push_back(move(document));
    for (auto& word : SplitIntoWords(docs_.back())) {
      auto& id_to_count = index_[word];
      if (!id_to_count.empty() && id_to_count.back().first == docs_.size() - 1) {
        ++id_to_count.back().second;
      } else {
        id_to_count.emplace_back(docs_.size() - 1, 1);
      }
    }
  }
}

const vector<pair<size_t, size_t>>& InvertedIndex::Lookup(string_view word) const {
  static vector<pair<size_t, size_t>> empty;
  if (auto it = index_.find(word); it != index_.end()) {
    return it->second;
  } else {
    return empty;
  }
}
