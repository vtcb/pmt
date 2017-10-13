#ifndef PMT_UKKONEN_CELL_H
#define PMT_UKKONEN_CELL_H

#include <vector>

class UkkonenCell  {
public:
  UkkonenCell();
  void setFinal();
  bool isFinal() const;
  bool hasNext(int ch) const;

  int& operator [](int ch);
  int at(int ch) const;

private:
  std::vector<int> next;
  bool final;
};

#endif /* PMT_UKKONEN_CELL_H */
