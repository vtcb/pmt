#ifndef PMT_SEARCH_ALGORITHM_H
#define PMT_SEARCH_ALGORITHM_H

#include <iostream>
#include <vector>

enum class SearchMode {
  COUNT,
  PRINT
};

// TODO(bolado): search should be common (for iterating through lines)
class SearchAlgorithm {
public:
  SearchAlgorithm(SearchMode mode, int max_error = 0);
  virtual void search(
      const std::vector<std::string>& pattern_list,
      const std::vector<std::string>& textfile_list) = 0;
  int getCount();

protected:
  void output(const std::string& line, int matches);
  int getMaxError();

private:
  SearchMode mode;
  int count;
  int max_error;
};

#endif /* PMT_SEARCH_ALGORITHM_H */
