#ifndef PMT_UKKONEN_NODE_H
#define PMT_UKKONEN_NODE_H

#include <unordered_map>

class UkkonenNode  {
public:
  UkkonenNode();
  void setId(int id);
  int getId() const;
  bool hasNext(int ch) const;

  int& operator [](int ch);
  int at(int ch) const;

private:
  std::unordered_map<int, int> next;
  int id;
};

#endif /* PMT_UKKONEN_NODE_H */
