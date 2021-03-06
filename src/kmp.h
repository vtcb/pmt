#ifndef PMT_KMP_H
#define PMT_KMP_H

#include <string>
#include <vector>

#include "search_algorithm.h"

class KMP : public SearchAlgorithm {
public:
  KMP(SearchMode mode);
  void search(
      const std::vector<std::string>& pattern_list,
      const std::vector<std::string>& textfile_list);

private:
  void search(
      const std::vector<std::string>& pattern_list, const std::string& text);
  int search(const std::string& pattern, 
  			 const std::string& text,
  			 const std::vector<int>& table);
  std::vector<int> kmpTable(const std::string& pattern);

  std::vector<std::vector<int>> tables;
};

#endif /* PMT_KMP_H */

