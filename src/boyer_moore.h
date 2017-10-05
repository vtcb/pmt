#ifndef PMT_BOYER_H
#define PMT_BOYER_H

#include <string>
#include <vector>

#include "search_algorithm.h"

class BoyerMoore : public SearchAlgorithm {
public:
  BoyerMoore(SearchMode mode);
  void search(
      std::vector<std::string> pattern_list,
      std::vector<std::string> textfile_list);

private:
  void search(std::vector<std::string> pattern_list, std::string text);
  int search(std::string pattern, std::string text);
  void badChar(std::string pattern);

  std::vector<int> bad_char_table;

};

#endif /* PMT_BOYER_H */
