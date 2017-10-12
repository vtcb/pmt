#include "ukkonen_trie.h"

UkkonenTrie::UkkonenTrie() : id_count(0) {}

int UkkonenTrie::add(const std::vector<int>& str) {
  int u = 0;
  for (int ch : str) {
    if (!nodes[u].hasNext(ch)) {
      nodes[u][ch] = nodes.size();
      nodes.push_back(UkkonenNode());
    }
    u = nodes[u][ch];
  }
  if (nodes[u].getId() == -1) {
    nodes[u].setId(id_count++);
  }
  return nodes[u].getId();
}

int UkkonenTrie::get(const std::vector<int>& str) {
  int u = 0;
  for (int ch : str) {
    if (!nodes[u].hasNext(ch)) {
      return -1;
    }
    u = nodes[u][ch];
  }
  return nodes[u].getId();
}
