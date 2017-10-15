#ifndef PMT_BITAP_H
#define PMT_BITAP_H

#include <vector>
#include <string>

#include "bitmask.h"
#include "search_algorithm.h"

class Bitap : public SearchAlgorithm {
public:
  Bitap(SearchMode mode);
  void search(
      const std::vector<std::string>& pattern_list,
      const std::vector<std::string>& textfile_list);

private:
  std::vector<std::vector<BitMask>> big_masks;
  std::vector<std::vector<uint64_t>> small_masks;
  void search(
      const std::vector<std::string>& pattern_list,
      const std::string& text);
  int search(
      unsigned int pattern_index,
      unsigned int pattern_size,
      const std::string& text);
  int searchBigPattern(
      const std::vector<BitMask>& pattern_mask,
      unsigned int pattern_size,
      const std::string& text);
  int searchSmallPattern(
      const std::vector<uint64_t>& pattern_mask,
      unsigned int pattern_size,
      const std::string& text);
  std::vector<BitMask> getBigMask(const std::string& pattern);
  std::vector<uint64_t> getSmallMask(const std::string& pattern);
};

#endif /* PMT_BITAP_H */
