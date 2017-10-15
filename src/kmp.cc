#include "kmp.h"

#include <fstream>
#include <string>
#include <vector>

#include "search_algorithm.h"

KMP::KMP(SearchMode mode) : SearchAlgorithm(mode) {}

void KMP::search(
    const std::vector<std::string>& pattern_list,
    const std::vector<std::string>& textfile_list) {

  tables.assign(pattern_list.size(), std::vector<int>());
  for (unsigned int i = 0; i < pattern_list.size(); i++) {
    tables[i] = std::move(kmpTable(pattern_list[i]));
  }

  for (std::string filename : textfile_list) {
    std::ifstream textfile(filename);
    std::string line;
    while (std::getline(textfile, line)) {
      search(pattern_list, line);
    }
  }
}

//KMP string searching searches for word "W" within text "S"
//by employing the observation that when a mismatch occurs,
//the word itself embodies sufficient information to determine
//where the next match could begin, thus bypassing re-examination
//of previously matched characters

//to avoid O(k*n), KMP spends a little time precomputing a table
//(on the order of the size of W[], O(n)) and uses it to do an 
//efficient search of the string in O(k)

//When KMP discovers a mismatch, the table determines how much
//KMP will increase (variable m) and where it resumes testing (i)

void KMP::search(
    const std::vector<std::string>& pattern_list,
    const std::string& text) {
  int matches = 0;
  for (unsigned int i = 0; i < pattern_list.size(); i++) {
    matches += search(pattern_list[i], text, tables[i]);
  }
  output(text, matches);
}

int KMP::search(const std::string& pattern, 
                const std::string& text,
                const std::vector<int>& table) {
  int matches = 0;
  int i = 0, j = 0;
  int n = text.size(), m = pattern.size();

  while (i < n) {
    while (j >= 0 && text[i] != pattern[j]) {
      j = table[j];
    }
    i++; j++;
    if (j == m) {
      matches++;
      j = table[j];
    }
  }

  return matches;
}

std::vector<int> KMP::kmpTable(const std::string& pattern) {
  std::vector<int> table(pattern.size() + 1);
  unsigned int position = 0;
  int candidate = -1;
  table[0] = -1;

  while (position < pattern.size()) {
    while (candidate >= 0 && pattern[position] != pattern[candidate]) {
      candidate = table[candidate];
    }
    candidate++;
    position++;
    table[position] = candidate;
  }

  return table;
}
