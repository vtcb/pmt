#include "ukkonen.h"

#include <fstream>
#include <string>
#include <vector>

#include "search_algorithm.h"

Ukkonen::Ukkonen(SearchMode mode, int max_error)
    : SearchAlgorithm(mode, max_error) {}

void Ukkonen::search(
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

void Ukkonen::search(
    const std::vector<std::string>& pattern_list, const std::string& text) {
  int matches = 0;
  for (const std::string& pattern : pattern_list) {
    matches += search(pattern, text);
  }
  output(text, matches);
}

int Ukkonen::search(const std::string& pattern, const std::string& text) {
  int matches = 0;
  return matches;
}
