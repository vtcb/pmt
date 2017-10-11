#include "sellers.h"

#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

#include "search_algorithm.h"

#include <iostream>

Sellers::Sellers(SearchMode mode, int max_error)
    : SearchAlgorithm(mode, max_error) {}

void Sellers::search(
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

void Sellers::search(
    const std::vector<std::string>& pattern_list, const std::string& text) {
  int matches = 0;
  for (const std::string& pattern : pattern_list) {
    matches += search(pattern, text);
  }
  output(text, matches);
}

bool Sellers::search(const std::string& pattern, const std::string& text) {
  const static int infinity = 0x3f3f3f3f;
  std::vector<int> T_(pattern.size());
  std::vector<int> T(pattern.size(), infinity);
  int error = infinity;

  auto ITERATION = [&](
      const std::vector<int>& T,
      const std::vector<int>& T_,
      int i) {
    T[0] = text[i] == pattern[0] ? 0 : 1;
    for (unsigned int j = 1; j < pattern.size(); j++) {
      int& cur = T[j];
      cur = infinity;
      cur = std::min(cur, T_[j]     + 1);
      cur = std::min(cur, T_[j - 1] + (text[i] != pattern[j]));
      cur = std::min(cur, T [j - 1] + 1);
    }
    error = std::min(error, T.back());
  };
 
  int MAX_SIZE = text.size() & ~1;
  for (unsigned int i = 0; i < MAX_SIZE; i += 2) {
    ITERATION(T_, T, i);
    ITERATION(T, T_, i + 1);
  }
  if (text.size() & 1) {
    ITERATION(T_, T, text.size() - 1);
  }

  return error <= getMaxError();
}
