#ifndef PMT_UKKONEN_NODE_H
#define PMT_UKKONEN_NODE_H

#include <unordered_map>

class UkkonenNode  {
public:
  UkkonenNode();
  void setId(int id);
  int getId();
  bool hasNext(int ch);

  int& operator [](int ch);

private:
  std::unordered_map<int, int> next;
  int id;
};

#endif /* PMT_UKKONEN_NODE_H */
