#include "bitap.h"

#include <fstream>
#include <string>
#include <vector>

#include "bitmask.h"
#include "search_algorithm.h"

Bitap::Bitap(SearchMode mode) : SearchAlgorithm(mode) {}

void Bitap::search(
    const std::vector<std::string>& pattern_list,
    const std::vector<std::string>& textfile_list) {
  big_masks.assign(pattern_list.size(), std::vector<BitMask>());
  small_masks.assign(pattern_list.size(), std::vector<uint64_t>());

  for (unsigned int i = 0; i < pattern_list.size(); i++) {
    const std::string& pattern = pattern_list[i];
    if (pattern.size() < 64) {
      small_masks[i] = std::move(getSmallMask(pattern));
    } else {
      big_masks[i] = std::move(getBigMask(pattern));
    }
  }

  for (std::string filename : textfile_list) {
    std::ifstream textfile(filename);
    std::string line;
    while (std::getline(textfile, line)) {
      search(pattern_list, line);
    }
  }
}

void Bitap::search(
    const std::vector<std::string>& pattern_list,
    const std::string& text) {
  int matches = 0;
  for (unsigned int i = 0; i < pattern_list.size(); i++) {
    matches += search(i, pattern_list[i].size(), text);
  }
  output(text, matches);
}

int Bitap::search(
    unsigned int pattern_index,
    unsigned int pattern_size,
    const std::string& text) {
  if (pattern_size < 64) {
    return searchSmallPattern(small_masks[pattern_index], pattern_size, text);
  } else {
    return searchBigPattern(big_masks[pattern_index], pattern_size, text);
  }
}

int Bitap::searchBigPattern(
    const std::vector<BitMask>& pattern_mask,
    unsigned int pattern_size,
    const std::string& text) {
  int matches = 0;
  BitMask mask = ~BitMask::one(pattern_size + 1);

  for (unsigned char ch : text) {
    mask = (mask | pattern_mask[ch]) << 1;

    if (mask[pattern_size] == 0) {
      matches++;
    }
  }

  return matches;
}

int Bitap::searchSmallPattern(
    const std::vector<uint64_t>& pattern_mask,
    unsigned int pattern_size,
    const std::string& text) {
  int matches = 0;
  uint64_t mask = ~uint64_t(1);
  uint64_t end_bit = uint64_t(1) << pattern_size;

  for (unsigned char ch : text) {
    mask = (mask | pattern_mask[ch]) << 1;

    if( (mask & end_bit) == 0) {
      matches++;
    }
  }

  return matches;
}

std::vector<BitMask> Bitap::getBigMask(const std::string& pattern) {
  std::vector<BitMask> pattern_mask(256, BitMask(pattern.size() + 1, 1));

  for (unsigned int i = 0; i < pattern.size(); i++) {
    pattern_mask[static_cast<unsigned char>(pattern[i])] =
        pattern_mask[static_cast<unsigned char>(pattern[i])]
            & ~(BitMask::one(pattern.size() + 1) << i);
  }

  return pattern_mask;
}

std::vector<uint64_t> Bitap::getSmallMask(const std::string& pattern) {
  std::vector<uint64_t> pattern_mask(256, ~uint64_t(0));

  for (unsigned int i = 0; i < pattern.size(); i++) {
    pattern_mask[static_cast<unsigned char>(pattern[i])] &= ~(uint64_t(1) << i);
  }

  return pattern_mask;
}
