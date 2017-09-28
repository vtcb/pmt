#ifndef PMT_AHO_NODE_H
#define PMT_AHO_NODE_H

#include <unordered_map>

class AhoNode {
private:
  // TODO(bolado): Consider optimazing it.
  std::unordered_map<char, int> next;
  int fail;
  int patterns;
public:
  AhoNode();
  bool hasNext(char ch);
  void addPattern();
  void addPatterns(int patterns);
  int getPatterns();
  int getFail();
  void setFail(int fail);

  std::unordered_map<char, int>::iterator begin();
  std::unordered_map<char, int>::iterator end();
  std::unordered_map<char, int>::const_iterator cbegin();
  std::unordered_map<char, int>::const_iterator cend();

  int& operator [](char ch) {
    return next[ch];
  }
};

#endif /* PMT_AHO_NODE_H */