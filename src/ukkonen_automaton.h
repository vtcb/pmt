#ifndef PMT_UKKONEN_AUTOMATON_H
#define PMT_UKKONEN_AUTOMATON_H

#include <vector>

#include "ukkonen_node.h"

class UkkonenAutomaton {
public:
  UkkonenAutomaton();
  void addNode();
  void addEdge(int u, int v, int c);
  void setFinal(int u);
  bool isFinal(int u);

private:
  std::vector<UkkonenNode> nodes;
};

#endif /* PMT_UKKONEN_AUTOMATON_H */
