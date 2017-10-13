#include "ukkonen_automaton.h"

#include "ukkonen_node.h"

UkkonenAutomaton::UkkonenAutomaton() {}

void UkkonenAutomaton::addNode() {
  nodes.push_back(UkkonenNode());
}

void UkkonenAutomaton::addEdge(int u, int v, int c) {
  nodes[u][c] = v;
}

void UkkonenAutomaton::setFinal(int u) {
  nodes[u].setId(1);
}

bool UkkonenAutomaton::isFinal(int u) {
  return nodes[u].getId() == 1;
}
