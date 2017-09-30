#ifndef PMT_BITMASK_H
#define PMT_BITMASK_H

#include <functional>
#include <vector>
#include "search_algorithm.h"

class BitMask {
public:
  BitMask(int size);
  int getSize();

  BitMask operator | (const BitMask& b) const {
    return this->forEach(b, [](int a, int b) -> int { return a | b; });
  }

  BitMask operator & (const BitMask& b) const {
    return this->forEach(b, [](int a, int b) -> int { return a & b; });
  }

  BitMask operator ^ (const BitMask& b) const {
    return this->forEach(b, [](int a, int b) -> int { return a ^ b; });
  }

  BitMask operator >> (int shift) const {
    BitMask b(size);

    for (int i = 0; i < size - shift; i++) {
      b.data[i] = data[i + shift];
    }

    return b;
  }

  BitMask operator << (int shift) const {
    BitMask b(size);

    for (int i = shift; i < size; i++) {
      b.data[i] = data[i - shift];
    }

    return b;
  }

private:
  BitMask forEach(const BitMask& b, std::function<int(int, int)> func) const;

  int size;
  std::vector<bool> data;
};

#endif /* PMT_BITMASK_H */
