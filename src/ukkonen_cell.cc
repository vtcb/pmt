#include "ukkonen_cell.h"

UkkonenCell::UkkonenCell() : next(256, -1), final(false) {}

void UkkonenCell::setFinal() {
  final = true;;
}

bool UkkonenCell::isFinal() const {
  return final;
}

bool UkkonenCell::hasNext(int ch) const {
  return next[ch] != -1;
}

int& UkkonenCell::operator [](int ch) {
  return next[ch];
}

int UkkonenCell::at(int ch) const {
  return next[ch];
}
