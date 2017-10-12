#include "ukkonen_node.h"

UkkonenNode::UkkonenNode() : id(-1) {}

void UkkonenNode::setId(int id) {
  this->id = id;
}

int UkkonenNode::getId() {
  return id;
}

bool UkkonenNode::hasNext(int ch) {
  return next.count(ch) > 0;
}

int& UkkonenNode::operator [](int ch) {
  return next[ch];
}
