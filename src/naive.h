#ifndef PMT_NAIVE_H
#define PMT_NAIVE_H

#include <string>
#include <vector>

#include "search_algorithm.h"

class Naive : public SearchAlgorithm {
public:
  Naive(SearchMode mode);
  void search(
      std::vector<std::string> pattern_list,
      std::vector<std::string> textfile_list);
  void search(std::vector<std::string> pattern_list, std::string text);
  int search(std::string pattern, std::string text);
};

#endif /* PMT_MATCH_H */
