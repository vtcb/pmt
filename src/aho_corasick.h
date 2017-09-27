#ifndef PMT_AHO_H
#define PMT_AHO_H

#include "search_algorithm.h"

class AhoCorasick : public SearchAlgorithm {
public:
  AhoCorasick(SearchMode mode);
  void search(
      std::vector<std::string> pattern_list,
      std::vector<std::string> textfile_list);
};

#endif /* PMT_AHO_H */
