#include "ukkonen_node.h"

UkkonenNode::UkkonenNode() : next(3, -1), id(-1) {}

void UkkonenNode::setId(int id) {
  this->id = id;
}

int UkkonenNode::getId() const {
  return id;
}

bool UkkonenNode::hasNext(int ch) const {
  return next[ch] != -1;
}

int& UkkonenNode::operator [](int ch) {
  return next[ch];
}

int UkkonenNode::at(int ch) const {
  return next.at(ch);
}
