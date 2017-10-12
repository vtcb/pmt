#include "ukkonen.h"

#include <fstream>
#include <queue>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include "search_algorithm.h"
#include "ukkonen_node.h"

Ukkonen::Ukkonen(SearchMode mode, int max_error)
    : SearchAlgorithm(mode, max_error) {}

void Ukkonen::search(
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

void Ukkonen::activate(const std::string& pattern) {
  std::queue<std::tuple<std::vector<int>, int>> q;
  std::vector<int> initial_column(pattern.size());
  int initial_state = 0;

  auto enqueue = [&](int state, const std::vector<int>& next_column) {
    int next_state = trie.get(next_column);
    if (next_state == -1) {
      next_state = trie.add(next_column);
    }
    q.push(std::tie(next_column, next_state));
    // Add edge from state to next_state
    if (next_column.back() < getMaxError()) {
      // Add to F :)
    }
  };

  // automata.add(initial_state);
  enqueue(initial_state, initial_column);

  while (!q.empty()) {
    std::vector<int> column;
    int state;
    std::tie(column, state) = std::move(q.front());
    q.pop();

    unsigned char ch = 255;
    do {
      enqueue(state, getNextColumn(column, pattern, ch));
    } while (ch--);
  }
}

std::vector<int> Ukkonen::getNextColumn(
    const std::vector<int>& old_column,
    const std::string& pattern,
    unsigned char ch) {
  std::vector<int> column(pattern.size());
  column[0] = ch == pattern[0] ? 0 : 1;
  for (unsigned int j = 1; j < pattern.size(); j++) {
    int& cur = column[j];
    cur = pattern.size();
    cur = std::min(cur, old_column[j]     + 1);
    cur = std::min(cur, old_column[j - 1] + (ch != pattern[j]));
    cur = std::min(cur,     column[j - 1] + 1);
  }
  return column;
}
