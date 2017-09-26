#include "naive.h"

#include <fstream>
#include <string>
#include <vector>

#include "search_algorithm.h"

void Naive::search(
    std::vector<std::string> pattern_list,
    std::vector<std::string> textfile_list) {
  for (std::string filename : textfile_list) {
    std::ifstream textfile(filename);
    std::string line;
    while (std::getline(textfile, line)) {
      std::cerr << "Line: " << line << std::endl; 
      search(pattern_list, line);
    }
  }
}

void Naive::search(std::vector<std::string> pattern_list, std::string text) {
  int matches = 0;
  for (std::string pattern : pattern_list) {
    matches += search(pattern, text);
  }
  output(text, matches);
}

int Naive::search(std::string pattern, std::string text) {
  int matches = 0;
  for (int i = 0; i < text.size() - pattern.size() + 1; i++) {
    int partial = 0;
    for (int j = 0; j < pattern.size(); j++) {
      if (text[i + j] != pattern[j]) break;
      partial++;
    }
    if (partial == pattern.size()) {
      matches++;
    }
  }
  return matches;
}
