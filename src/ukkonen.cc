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
  int initial_state = 0;
  std::vector<int> initial_column(pattern.size());

  for (unsigned int i = 0; i < pattern.size(); i++) {
    initial_column[i] = i + 1;
  }

  automaton.addNode();
  trie.add(initial_column);
  q.push(std::tie(initial_column, initial_state));

  while (!q.empty()) {
    std::vector<int> column;
    int state;
    std::tie(column, state) = std::move(q.front());
    q.pop();

    if (column.back() <= getMaxError()) {
      automaton.setFinal(state);
    }

    unsigned char ch = 255;
    do {
    std::vector<int> next_column =
        std::move(getNextColumn(column, pattern, ch));
    int next_state = trie.get(next_column);
    if (next_state == -1) {
      next_state = trie.add(next_column);
      automaton.addNode();
    }
    q.push(std::tie(next_column, next_state));
    automaton.addEdge(state, next_state, ch);
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
