#ifndef PMT_NAIVE_H
#define PMT_NAIVE_H

#include <string>
#include <vector>

#include "search_algorithm.h"

class Naive : public SearchAlgorithm {
public:
  Naive(SearchMode mode);
  void search(
      const std::vector<std::string>& pattern_list,
      const std::vector<std::string>& textfile_list);

private:
  void search(
      const std::vector<std::string>& pattern_list, const std::string& text);
  int search(const std::string& pattern, const std::string& text);
};

#endif /* PMT_NAIVE_H */
