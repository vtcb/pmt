#ifndef PMT_UKKONEN_H
#define PMT_UKKONEN_H

#include <string>
#include <vector>

#include "search_algorithm.h"
#include "ukkonen_trie.h"

class Ukkonen : public SearchAlgorithm {
public:
  Ukkonen(SearchMode mode, int max_error = 0);
  void search(
      const std::vector<std::string>& pattern_list,
      const std::vector<std::string>& textfile_list);

private:
  UkkonenTrie trie;
  void search(
      const std::vector<std::string>& pattern_list, const std::string& text);
  int search(const std::string& pattern, const std::string& text);
};

#endif /* PMT_UKKONEN_H */
