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
  int search(
      const std::string& pattern, const std::string& text,
      const std::vector<int>& bad_char_table,
      const std::vector<int>& shift_table);
  std::vector<int> badChar(const std::string& pattern);
  std::vector<int> goodSuffix(const std::string& pattern);

  std::vector<std::vector<int>> bad_char_tables;
  std::vector<std::vector<int>> shift_tables;

};

#endif /* PMT_BOYER_H */
