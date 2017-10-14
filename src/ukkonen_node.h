#ifndef PMT_UKKONEN_NODE_H
#define PMT_UKKONEN_NODE_H

#include <vector>

class UkkonenNode  {
public:
  UkkonenNode();
  void setId(int id);
  int getId() const;
  bool hasNext(int ch) const;

  int& operator [](int ch);
  int at(int ch) const;

private:
  std::vector<int> next;
  int id;
};

#endif /* PMT_UKKONEN_NODE_H */
