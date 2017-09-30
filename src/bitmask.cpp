#include "bitmask.h"

#include <algorithm>
#include <functional>

BitMask::BitMask(int size) : size(size), data(size, 0) {}

int BitMask::getSize() {
  return size;
}

BitMask BitMask::forEach(
    const BitMask& that, std::function<int(int, int)> func) const {
  BitMask c(std::max(this->size, that.size));

  for (int i = 0; i < std::min(this->size, that.size); i++) {
    c.data[i] = func(this->data[i], that.data[i]);
  }

  if (this->size > that.size) {
    for (int i = that.size; i < this->size; i++) {
      c.data[i] = func(this->data[i], 0);
    }
  } else {
    for (int i = this->size; i < that.size; i++) {
      c.data[i] = func(0, that.data[i]);
    }
  }

  return c;
}
