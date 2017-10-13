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
    // Exact matching
    if (max_error == 0) {
      // Several patterns
      if (pattern_list.size() > 2) {
        return new AhoCorasick(search_mode);
      }

      unsigned int max_size = 0;
      for (const std::string& pattern : pattern_list) {
        max_size = std::max(max_size, (unsigned int) pattern.size());
      }

      // Small patterns
      if (max_size < 64) {
        return new Bitap(search_mode);
      }

      // Otherwise
      return new KMP(search_mode);
    }

    // Approximate matching
    // TODO(bolado): Consider a threshold for max_error and pattern size, as
    //     Ukkonen's complexity grows exponentially.
    return new Ukkonen(search_mode, max_error);
  }
};

#endif /* PMT_ALGORITHM_CHOOSER_H */
