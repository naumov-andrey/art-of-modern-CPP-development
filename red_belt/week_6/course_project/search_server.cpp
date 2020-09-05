#include "search_server.h"
#include "iterator_range.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
#include <numeric>

vector<string> SplitIntoWords(string line) {
  std::istringstream wordsInput(line);
  return {std::make_move_iterator(std::istream_iterator<std::string>(wordsInput)),
          std::make_move_iterator(std::istream_iterator<std::string>()) };
}

SearchServer::SearchServer(istream& document_input) {
  UpdateDocumentBase(document_input);
}


void SearchServer::UpdateDocumentBase(istream& document_input) {
  InvertedIndex new_index;

  for (string current_document; getline(document_input, current_document); ) {
    new_index.Add(move(current_document));
  }

  swap(index_, new_index);
}

void SearchServer::AddQueriesStream(istream& query_input, ostream& search_results_output) {
  vector<pair<size_t, size_t>> docid_count;
  for (string current_query; getline(query_input, current_query); ) {
    docid_count.assign(index_.GetDocsCount(), {0, 0});
    const auto words = SplitIntoWords(current_query);

    for (const auto& word : words) {
      for (auto& id_to_count : index_.Lookup(word)) {
        docid_count[id_to_count.first].first = id_to_count.first;
        docid_count[id_to_count.first].second += id_to_count.second;
      }
    }

    partial_sort(
      docid_count.begin(),
      docid_count.begin() + min(5ul, docid_count.size()),
      docid_count.end(),
      [&](const auto& lhs, const auto& rhs) {
        return pair(lhs.second, rhs.first) > pair(rhs.second, lhs.first);
      }
    );

    search_results_output << current_query << ':';
    for (const auto& i : Head(docid_count, 5)) {
      if (i.second == 0) {
        break;
      }
      search_results_output << " {"
        << "docid: " << i.first << ", "
        << "hitcount: " << i.second << '}';
    }
    search_results_output << endl;
  }
}

void InvertedIndex::Add(string document) {
  for (auto& word : SplitIntoWords(move(document))) {
    auto& id_to_count = index_[move(word)];
    if (!id_to_count.empty() && id_to_count.back().first == docs_count_) {
      ++id_to_count.back().second;
    } else {
      id_to_count.emplace_back(docs_count_, 1);
    }
  }
  ++docs_count_;
}

vector<pair<size_t, size_t>> InvertedIndex::Lookup(const string& word) const {
  if (auto it = index_.find(word); it != index_.end()) {
    return it->second;
  } else {
    return {};
  }
}
