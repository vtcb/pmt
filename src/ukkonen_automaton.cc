#include "ukkonen_automaton.h"

#include "ukkonen_cell.h"

UkkonenAutomaton::UkkonenAutomaton() {}

void UkkonenAutomaton::addNode() {
  nodes.push_back(UkkonenCell());
}

void UkkonenAutomaton::addEdge(int u, int v, int c) {
  nodes[u][c] = v;
}
int UkkonenAutomaton::getNext(int u, int c) const {
  return nodes[u].at(c);
}

void UkkonenAutomaton::setFinal(int u) {
  nodes[u].setFinal();
}

bool UkkonenAutomaton::isFinal(int u) const {
  return nodes[u].isFinal();
}
