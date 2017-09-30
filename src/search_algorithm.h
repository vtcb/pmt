#ifndef PMT_SEARCH_ALGORITHM_H
#define PMT_SEARCH_ALGORITHM_H

#include <iostream>
#include <vector>

enum class SearchMode {
  COUNT,
  PRINT
};

class SearchAlgorithm {
public:
  SearchAlgorithm(SearchMode mode);
  virtual void search(
      std::vector<std::string> pattern_list,
      std::vector<std::string> textfile_list) = 0;
  int getCount();

protected:
  void output(const std::string& line, int matches);

private:
  SearchMode mode;
  int count;
};

#endif /* PMT_SEARCH_ALGORITHM_H */
