#include "aho_node.h"

AhoNode::AhoNode() : fail(0), patterns(0) {}

bool AhoNode::hasNext(char ch) {
  return next.count(ch);
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

std::unordered_map<char, int>::iterator AhoNode::begin() {
  return next.begin();
}

std::unordered_map<char, int>::iterator AhoNode::end() {
  return next.end();
}

std::unordered_map<char, int>::const_iterator AhoNode::cbegin() {
  return next.cbegin();
}

std::unordered_map<char, int>::const_iterator AhoNode::cend() {
  return next.cend();
}
