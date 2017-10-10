#include "boyer_moore.h"

#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

#include "search_algorithm.h"

#define ALPHABET 256

BoyerMoore::BoyerMoore(SearchMode mode) : SearchAlgorithm(mode) {}

void BoyerMoore::search(
    std::vector<std::string> pattern_list,
    std::vector<std::string> textfile_list) {

  for (std::string filename : textfile_list) {
    std::ifstream textfile(filename);
    std::string line;
    while (std::getline(textfile, line)) {
      search(pattern_list, line);
    }
  }
}

void BoyerMoore::search(std::vector<std::string> pattern_list, std::string text) {
  int matches = 0;

  for (std::string pattern : pattern_list) {
    bad_char_table.assign(ALPHABET, -1);
    badChar(pattern);
    matches += search(pattern, text);
  }
  output(text, matches);
}

//BAD_CHAR

int BoyerMoore::search(std::string pattern, std::string text) {
  int matches = 0;

  unsigned int shift = 0;

  while (shift <= (text.size() - pattern.size() + 1)){

    int cur_char = pattern.size() - 1;
    while(cur_char >= 0 && pattern[cur_char] == text[shift+cur_char]){
      cur_char--;
    }
    if(cur_char < 0){
      matches++;
      if(shift + pattern.size() < text.size()) {
        shift += pattern.size() - bad_char_table[text[shift+pattern.size()]];
      } else {
        shift += 1;
      }
    } else {
      shift += std::max(1, cur_char - bad_char_table[text[shift+cur_char]]);
    }

  }

  return matches;
}

void BoyerMoore::badChar(std::string pattern) {

  //Last appearance of a character on the pattern
  for(unsigned int i = 0; i < pattern.size(); i++){
    bad_char_table[static_cast<int>(pattern[i])] = i;
  }

}
