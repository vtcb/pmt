#ifndef PMT_SELLERS_H
#define PMT_SELLERS_H

#include <string>
#include <vector>

#include "search_algorithm.h"

class Sellers : public SearchAlgorithm {
public:
  Sellers(SearchMode mode, int max_error = 0);
  void search(
      const std::vector<std::string>& pattern_list,
      const std::vector<std::string>& textfile_list);

private:
  void search(
      const std::vector<std::string>& pattern_list, const std::string& text);
  bool search(const std::string& pattern, const std::string& text);
};

#endif /* PMT_SELLERS_H */
