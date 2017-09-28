#ifndef PMT_AHO_H
#define PMT_AHO_H

#include "search_algorithm.h"

#include <vector>
#include <string>
#include "aho_node.h"

class AhoCorasick : public SearchAlgorithm {
private:
  std::vector<AhoNode> nodes;
public:
  AhoCorasick(SearchMode mode);
  void search(
      std::vector<std::string> pattern_list,
      std::vector<std::string> textfile_list);
  void add(const std::string& str);
  void activate();
  void traverse(int u = 0, std::string s = "");
};

#endif /* PMT_AHO_H */
