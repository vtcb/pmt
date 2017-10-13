#ifndef PMT_UKKONEN_TRIE_H
#define PMT_UKKONEN_TRIE_H

#include <vector>
#include "ukkonen_node.h"

class UkkonenTrie  {
public:
  UkkonenTrie();
  int add(const std::vector<int>& str);
  int get(const std::vector<int>& str) const;

private:
  std::vector<UkkonenNode> nodes;
  int id_count;
};

#endif /* PMT_UKKONEN_TRIE_H */
