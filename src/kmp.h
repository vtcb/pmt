#ifndef PMT_KMP_H
#define PMT_KMP_H

#include <string>
#include <vector>

#include "search_algorithm.h"

class KMP : public SearchAlgorithm {
private:
  std::vector<int> table;
public:
  KMP(SearchMode mode);
  void search(
      std::vector<std::string> pattern_list,
      std::vector<std::string> textfile_list);
  void search(std::vector<std::string> pattern_list, std::string text);
  int search(std::string pattern, std::string text);
  void kmp_table(std::string pattern);
};

#endif /* PMT_KMP_H */
