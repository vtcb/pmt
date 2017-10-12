#include "ukkonen.h"

#include <fstream>
#include <string>
#include <vector>

#include "search_algorithm.h"
#include "ukkonen_node.h"

Ukkonen::Ukkonen(SearchMode mode, int max_error)
    : SearchAlgorithm(mode, max_error), id_count(0) {}

void Ukkonen::add(const std::vector<int>& str) {
  int u = 0;
  for (int ch : str) {
    if (!nodes[u].hasNext(ch)) {
      nodes[u][ch] = nodes.size();
      nodes.push_back(UkkonenNode());
    }
    u = nodes[u][ch];
  }
  if (nodes[u].getId() == -1) {
    nodes[u].setId(id_count++);
  }
}

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
