#ifndef PMT_BITMASK_H
#define PMT_BITMASK_H

#include <functional>
#include <string>
#include <vector>
#include "search_algorithm.h"

typedef unsigned long long int BitMaskDataType;

class BitMask {
public:
  BitMask(unsigned int size, int value = 0);
  BitMask(const BitMask& mask);
  unsigned int getSize() const;

  static const unsigned int DATA_SIZE = sizeof(BitMaskDataType) * 8 - 1;
  static const BitMaskDataType DATA_ONE = BitMaskDataType(1);
  static const BitMaskDataType DATA_LAST = DATA_ONE << (DATA_SIZE - 1);

  static BitMask one(unsigned int size = 1) {
    BitMask mask(size);
    if (size > 0) {
      mask.data[0] = 1;
    }
    return mask;
  }

  BitMask shiftLeft() const;
  BitMask shiftRight() const;

  BitMask operator | (const BitMask& b) const {
    return this->forEach(
        b, [](BitMaskDataType a, BitMaskDataType b) -> BitMaskDataType {
          return a | b; });
  }

  BitMask operator & (const BitMask& b) const {
    return this->forEach(
        b, [](BitMaskDataType a, BitMaskDataType b) -> BitMaskDataType {
          return a & b; });
  }

  BitMask operator ^ (const BitMask& b) const {
    return this->forEach(
        b, [](BitMaskDataType a, BitMaskDataType b) -> BitMaskDataType {
          return a ^ b; });
  }

  BitMask operator ~ () const {
    BitMask b(size);

    for (unsigned int i = 0; i < data.size(); i++) {
      b.data[i] = ~data[i];
    }

    b.fixBack();

    return b;
  }

  BitMask operator >> (int shift) const {
    BitMask b(*this);

    while (shift--) {
      b = b.shiftRight();
    }

    return b;
  }

  BitMask operator << (int shift) const {
    BitMask b(*this);

    while (shift--) {
      b = b.shiftLeft();
    }

    return b;
  }

  bool operator [] (int idx) const {
    return data[idx / DATA_SIZE] & (DATA_ONE << (idx % DATA_SIZE));
  }

  operator std::string() const {
    std::string str = "[";

    for (int i = size - 1; i >= 0; i--) {
      str += (*this)[i] ? "1" : "0";
    }

    str += "]";
    return str;
  }

private:
  BitMask forEach(
      const BitMask& b,
      std::function<
          BitMaskDataType(BitMaskDataType, BitMaskDataType)> func) const;

  void fixBack();

  unsigned int size;
  std::vector<BitMaskDataType> data;
};

#endif /* PMT_BITMASK_H */
