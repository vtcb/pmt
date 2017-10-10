#include "bitmask.h"

#include <algorithm>
#include <functional>
#include <ostream>

BitMask::BitMask(unsigned int size, int value)
    : size(size),
      data(
          (size + BitMask::DATA_SIZE - 1) / BitMask::DATA_SIZE,
          value ? ~BitMaskDataType(0) : 0) {
  fixBack();
}

BitMask::BitMask(const BitMask& mask) : size(mask.size), data(mask.data) {}

unsigned int BitMask::getSize() const {
  return size;
}

BitMask BitMask::shiftLeft() const {
  BitMask b(size);

  bool carry = false;
  for (unsigned int i = 0; i < data.size(); i++) {
    b.data[i] = data[i] << 1;
    if (carry) {
      b.data[i] |= BitMask::DATA_ONE;
    }
    carry = data[i] & BitMask::DATA_LAST;
  }

  return b;
}

BitMask BitMask::shiftRight() const {
  BitMask b(size);

  bool carry = false;
  for (int i = static_cast<int>(data.size() - 1); i >= 0; i--) {
    b.data[i] = data[i] >> 1;
    if (carry) {
      b.data[i] |= BitMask::DATA_LAST;
    }
    carry = data[i] & BitMask::DATA_ONE;
  }

  b.fixBack();  

  return b;
}

BitMask BitMask::forEach(
    const BitMask& that,
    std::function<
        BitMaskDataType(BitMaskDataType, BitMaskDataType)> func) const {
  BitMask c(std::max(this->getSize(), that.getSize()));
  unsigned int sizeA = this->data.size();
  unsigned int sizeB = that.data.size();

  for (unsigned int i = 0; i < std::min(sizeA, sizeB); i++) {
    c.data[i] = func(this->data[i], that.data[i]);
  }

  if (sizeA > sizeB) {
    for (unsigned int i = sizeB; i < sizeA; i++) {
      c.data[i] = func(this->data[i], 0);
    }
  } else {
    for (unsigned int i = sizeA; i < sizeA; i++) {
      c.data[i] = func(0, that.data[i]);
    }
  }

  return c;
}

void BitMask::fixBack() {
  if (size % BitMask::DATA_SIZE) {
    data.back() &= (BitMask::DATA_ONE << ((size % BitMask::DATA_SIZE) + 1)) - 1;
  }
}
