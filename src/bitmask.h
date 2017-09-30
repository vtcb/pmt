#ifndef PMT_BITMASK_H
#define PMT_BITMASK_H

#include <functional>
#include <string>
#include <vector>
#include "search_algorithm.h"

class BitMask {
public:
  BitMask(int size, int value = 0);
  int getSize() const;

  static BitMask one(int size = 1) {
    BitMask mask(size);
    mask.data[0] = 1;
    return mask;
  }

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

  BitMask operator ~ () const {
    BitMask b(size);

    for (int i = 0; i < size; i++) {
      b.data[i] = !data[i];
    }

    return b;
  }

  bool operator [] (int idx) const {
    return data[idx];
  }

  operator std::string() const {
    std::string str = "[";

    for (int i = size - 1; i >= 0; i--) {
      str += data[i] ? "1" : "0";
    }

    str += "]";
    return str;
  }

private:
  BitMask forEach(const BitMask& b, std::function<int(int, int)> func) const;

  int size;
  std::vector<bool> data;
};

#endif /* PMT_BITMASK_H */
