#ifndef PMT_BITAP_H
#define PMT_BITAP_H

#include <vector>
#include <string>

#include "search_algorithm.h"

class Bitap : public SearchAlgorithm {
public:
  Bitap(SearchMode mode);
  void search(
      std::vector<std::string> pattern_list,
      std::vector<std::string> textfile_list);

private:
  void search(std::vector<std::string> pattern_list, std::string text);
  int search(std::string pattern, std::string text);
};

#endif /* PMT_BITAP_H */
