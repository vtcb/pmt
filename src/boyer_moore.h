#ifndef PMT_BOYER_H
#define PMT_BOYER_H

#include <string>
#include <vector>

#include "search_algorithm.h"

class BoyerMoore : public SearchAlgorithm {
public:
  BoyerMoore(SearchMode mode);
  void search(
      const std::vector<std::string>& pattern_list,
      const std::vector<std::string>& textfile_list);

private:
  void search(
      const std::vector<std::string>& pattern_list, const std::string& text);
  int search(const std::string& pattern, const std::string& text);
  void badChar(const std::string& pattern);
  void goodSuffix(const std::string& pattern);
  void preProcessing(const std::string& pattern);

  std::vector<int> bad_char_table;
  std::vector<int> shift_table;
  std::vector<int> border_position;

};

#endif /* PMT_BOYER_H */
