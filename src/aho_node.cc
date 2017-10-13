#include "aho_node.h"

AhoNode::AhoNode() : next(256, -1), fail(0), patterns(0) {}

bool AhoNode::hasNext(unsigned char ch) {
  return next[ch] != -1;
}

void AhoNode::addPattern() {
  patterns++;
}

void AhoNode::addPatterns(int patterns) {
  this->patterns += patterns;
}

int AhoNode::getPatterns() {
  return patterns;
}

int AhoNode::getFail() {
  return fail;
}

void AhoNode::setFail(int fail) {
  this->fail = fail;
}

std::vector<int>::iterator AhoNode::begin() {
  return next.begin();
}

std::vector<int>::iterator AhoNode::end() {
  return next.end();
}

std::vector<int>::const_iterator AhoNode::cbegin() {
  return next.cbegin();
}

std::vector<int>::const_iterator AhoNode::cend() {
  return next.cend();
}
