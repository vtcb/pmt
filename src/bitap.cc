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
  for (std::string pattern : pattern_list) {
    matches += search(pattern, text);
  }
  output(text, matches);
}

int Bitap::search(const std::string& pattern, const std::string& text) {
  if (pattern.size() < 64) {
    return searchSmallPattern(pattern, text);
  } else {
    return searchAnyPattern(pattern, text);
  }
}

int Bitap::searchAnyPattern(
    const std::string& pattern, const std::string& text) {
  int matches = 0;
  std::vector<BitMask> pattern_mask(256, BitMask(pattern.size() + 1, 1));
  BitMask mask = ~BitMask::one(pattern.size() + 1);

  for (unsigned int i = 0; i < pattern.size(); i++) {
    pattern_mask[static_cast<unsigned char>(pattern[i])] =
        pattern_mask[static_cast<unsigned char>(pattern[i])]
            & ~(BitMask::one(pattern.size() + 1) << i);
  }

  for (unsigned char ch : text) {
    mask = (mask | pattern_mask[ch]) << 1;

    if (mask[pattern.size()] == 0) {
      matches++;
    }
  }

  return matches;
}

int Bitap::searchSmallPattern(
    const std::string& pattern, const std::string& text) {
  int matches = 0;
  std::vector<uint64_t> pattern_mask(256, ~uint64_t(0));
  uint64_t mask = ~uint64_t(1);
  uint64_t end_bit = uint64_t(1) << pattern.size();

  for (unsigned int i = 0; i < pattern.size(); i++) {
    pattern_mask[static_cast<unsigned char>(pattern[i])] &= ~(uint64_t(1) << i);
  }

  for (unsigned char ch : text) {
    mask = (mask | pattern_mask[ch]) << 1;

    if( (mask & end_bit) == 0) {
      matches++;
    }
  }

  return matches;
}
