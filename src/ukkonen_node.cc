#include "ukkonen_node.h"

UkkonenNode::UkkonenNode() : id(-1) {}

void UkkonenNode::setId(int id) {
  this->id = id;
}

int UkkonenNode::getId() const {
  return id;
}

bool UkkonenNode::hasNext(int ch) const {
  return next.count(ch) > 0;
}

int& UkkonenNode::operator [](int ch) {
  return next[ch];
}

int UkkonenNode::at(int ch) const {
  return next.at(ch);
}
