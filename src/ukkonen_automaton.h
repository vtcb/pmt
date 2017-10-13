#ifndef PMT_UKKONEN_AUTOMATON_H
#define PMT_UKKONEN_AUTOMATON_H

#include <vector>

#include "ukkonen_cell.h"

class UkkonenAutomaton {
public:
  UkkonenAutomaton();
  void addNode();
  void addEdge(int u, int v, int c);
  int getNext(int u, int c) const;
  void setFinal(int u);
  bool isFinal(int u) const;

private:
  std::vector<UkkonenCell> nodes;
};

#endif /* PMT_UKKONEN_AUTOMATON_H */
