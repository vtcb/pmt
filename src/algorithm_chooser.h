#ifndef PMT_ALGORITHM_CHOOSER_H
#define PMT_ALGORITHM_CHOOSER_H

#include <algorithm>
#include <string>
#include <vector>

#include "search_algorithm.h"
#include "search_algorithms.h"

class AlgorithmChooser {
public:
  static SearchAlgorithm* choose(
      const std::vector<std::string>& pattern_list,
      SearchMode                      search_mode,
      int                             max_error) {
    unsigned int max_size = 0;
    for (const std::string& pattern : pattern_list) {
      max_size = std::max(max_size, (unsigned int) pattern.size());
    }

    // Exact matching
    if (max_error == 0) {
      if (max_size == 1) {
        return new Naive(search_mode);
      }

      // Several patterns
      if (pattern_list.size() > 5) {
        return new AhoCorasick(search_mode);
      }

      // Small patterns
      if (max_size < 64) {
        return new Bitap(search_mode);
      }

      // Otherwise
      return new BoyerMoore(search_mode);
    }

    // Approximate matching
    if (max_error <= 15 || max_size <= 15) {
      return new Ukkonen(search_mode, max_error);
    }
    return new Sellers(search_mode, max_error);
  }
};

#endif /* PMT_ALGORITHM_CHOOSER_H */
