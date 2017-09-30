#ifndef PMT_AHO_H
#define PMT_AHO_H

#include "search_algorithm.h"

#include <vector>
#include <string>
#include "aho_node.h"

class AhoCorasick : public SearchAlgorithm {
public:
  AhoCorasick(SearchMode mode);
  void search(
      std::vector<std::string> pattern_list,
      std::vector<std::string> textfile_list);

private:
  void add(const std::string& str);
  void activate();
  void traverse(int u = 0, std::string s = "");
  int search(const std::string& text);

  std::vector<AhoNode> nodes;
};

#endif /* PMT_AHO_H */
