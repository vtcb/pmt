#include "ukkonen_trie.h"

UkkonenTrie::UkkonenTrie() : nodes(1), id_count(0) {}

int UkkonenTrie::add(const std::vector<int>& str) {
  int u = 0;
  int last = 0;
  for (int ch : str) {
    int edge = ch - last + 1;
    if (!nodes[u].hasNext(edge)) {
      nodes[u][edge] = nodes.size();
      nodes.push_back(UkkonenNode());
    }
    u = nodes[u][edge];
    last = ch;
  }
  if (nodes[u].getId() == -1) {
    nodes[u].setId(id_count++);
  }
  return nodes[u].getId();
}

int UkkonenTrie::get(const std::vector<int>& str) const {
  int u = 0;
  int last = 0;
  for (int ch : str) {
    int edge = ch - last + 1;
    if (!nodes[u].hasNext(edge)) {
      return -1;
    }
    u = nodes[u].at(edge);
    last = ch;
  }
  return nodes[u].getId();
}
