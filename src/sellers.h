#ifndef PMT_SELLERS_H
#define PMT_SELLERS_H

#include <string>
#include <vector>

#include "search_algorithm.h"

class Sellers : public SearchAlgorithm {
public:
  Sellers(SearchMode mode, int max_error = 0);
  void search(
      std::vector<std::string> pattern_list,
      std::vector<std::string> textfile_list);

private:
  void search(std::vector<std::string> pattern_list, std::string text);
  bool search(std::string pattern, std::string text);
};

#endif /* PMT_SELLERS_H */
