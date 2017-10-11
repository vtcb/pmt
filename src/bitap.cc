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
  int matches = 0;
  std::vector<BitMask> pattern_mask(300, BitMask(pattern.size() + 1, 1));
  BitMask mask = ~BitMask::one(pattern.size() + 1);

  for (unsigned int i = 0; i < pattern.size(); i++) {
    pattern_mask[pattern[i]] =
        pattern_mask[pattern[i]] & ~(BitMask::one(pattern.size() + 1) << i);
  }

  for (char ch : text) {
    mask = (mask | pattern_mask[ch]) << 1;

    if (mask[pattern.size()] == 0) {
      matches++;
    }
  }

  return matches;
}
