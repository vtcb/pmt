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
  for (std::string pattern : pattern_list) {
    matches += search(pattern, text);
  }
  output(text, matches);
}

bool Sellers::search(const std::string& pattern, const std::string& text) {
  const static int infinity = 0x3f3f3f3f;
  std::vector<int> T_(pattern.size());
  std::vector<int> T(pattern.size(), infinity);
  int error = infinity;

  auto getT = [&](int di, int dj) -> int {
    return dj >= 0 ? (di == 0 ? T : T_)[dj] : 0;
  };

  for (unsigned int i = 0; i < text.size(); i++) {
    swap(T, T_);
    for (unsigned int j = 0; j < pattern.size(); j++) {
      T[j] = infinity;
      T[j] = std::min(T[j], getT(-1, j)     + 1);
      T[j] = std::min(T[j], getT(-1, j - 1) + (text[i] != pattern[j]));
      T[j] = std::min(T[j], getT( 0, j - 1) + 1);
    }
    error = std::min(error, T.back());
  }

  return error <= getMaxError();
}
