#ifndef PMT_AHO_NODE_H
#define PMT_AHO_NODE_H

#include <vector>

class AhoNode {
public:
  AhoNode();
  bool hasNext(unsigned char ch);
  void addPattern();
  void addPatterns(int patterns);
  int getPatterns();
  int getFail();
  void setFail(int fail);

  std::vector<int>::iterator begin();
  std::vector<int>::iterator end();
  std::vector<int>::const_iterator cbegin();
  std::vector<int>::const_iterator cend();

  int& operator [](char ch) {
    return next[ch];
  }

private:
  std::vector<int> next;
  int fail;
  int patterns;
};

#endif /* PMT_AHO_NODE_H */
