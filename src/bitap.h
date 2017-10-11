#ifndef PMT_BITAP_H
#define PMT_BITAP_H

#include <vector>
#include <string>

#include "search_algorithm.h"

class Bitap : public SearchAlgorithm {
public:
  Bitap(SearchMode mode);
  void search(
      const std::vector<std::string>& pattern_list,
      const std::vector<std::string>& textfile_list);

private:
  void search(
      const std::vector<std::string>& pattern_list, const std::string& text);
  int search(const std::string& pattern, const std::string& text);
};

#endif /* PMT_BITAP_H */
