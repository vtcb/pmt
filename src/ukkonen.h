#ifndef PMT_UKKONEN_H
#define PMT_UKKONEN_H

#include <string>
#include <vector>

#include "search_algorithm.h"
#include "ukkonen_trie.h"
#include "ukkonen_automaton.h"

class Ukkonen : public SearchAlgorithm {
public:
  Ukkonen(SearchMode mode, int max_error = 0);
  void search(
      const std::vector<std::string>& pattern_list,
      const std::vector<std::string>& textfile_list);

private:
  UkkonenTrie trie;
  std::vector<UkkonenAutomaton> automata;
  void search(const std::string& text);
  int search(const UkkonenAutomaton& automaton, const std::string& text);

  UkkonenAutomaton activate(const std::string& pattern);
  std::vector<int> getNextColumn(
      const std::vector<int>& column,
      const std::string& pattern,
      unsigned char ch);
};

#endif /* PMT_UKKONEN_H */
