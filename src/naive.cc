#include "naive.h"

#include <fstream>
#include <string>
#include <vector>

#include "search_algorithm.h"

Naive::Naive(SearchMode mode) : SearchAlgorithm(mode) {}

void Naive::search(
    const std::vector<std::string>& pattern_list,
    const std::vector<std::string>& textfile_list) {
  for (const std::string& filename : textfile_list) {
    std::ifstream textfile(filename);
    std::string line;
    while (std::getline(textfile, line)) {
      search(pattern_list, line);
    }
  }
}

void Naive::search(
    const std::vector<std::string>& pattern_list, const std::string& text) {
  int matches = 0;
  for (const std::string& pattern : pattern_list) {
    matches += search(pattern, text);
  }
  output(text, matches);
}

int Naive::search(const std::string& pattern, const std::string& text) {
  if (text.size() < pattern.size()) return 0;
  int matches = 0;
  unsigned int m = pattern.size();
  for (int i = static_cast<int>(text.size() - pattern.size()); i >= 0; i--) {
    unsigned int j = 0;
    for (; j < m; j++) {
      if (text[i + j] != pattern[j]) break;
    }
    if (j == m) {
      matches++;
    }
  }
  return matches;
}
