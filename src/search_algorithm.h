#ifndef PMT_SEARCH_ALGORITHM_H
#define PMT_SEARCH_ALGORITHM_H

#include <iostream>
#include <vector>

enum class SearchMode {
  COUNT,
  PRINT
};

class SearchAlgorithm {
private:
  SearchMode mode;
  int count;
public:
  SearchAlgorithm(SearchMode mode);
  void output(const std::string& line, int matches);
  int getCount();
  virtual void search(
      std::vector<std::string> pattern_list,
      std::vector<std::string> textfile_list) = 0;
};

#endif /* PMT_SEARCH_ALGORITHM_H */
