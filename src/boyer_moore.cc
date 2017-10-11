#include "boyer_moore.h"

#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

#include "search_algorithm.h"

#define ALPHABET 256

BoyerMoore::BoyerMoore(SearchMode mode) : SearchAlgorithm(mode) {}

void BoyerMoore::search(
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

void BoyerMoore::search(
    const std::vector<std::string>& pattern_list,
    const std::string& text) {
  int matches = 0;

  for (std::string pattern : pattern_list) {
    preProcessing(pattern);
    matches += search(pattern, text);
  }
  output(text, matches);
}

void BoyerMoore::preProcessing(const std::string& pattern){
    bad_char_table.assign(ALPHABET, -1);
    shift_table.assign(pattern.size()+1, 0);
    border_position.assign(pattern.size()+1, 0);
    badChar(pattern);
    goodSuffix(pattern);
}

//BAD_CHAR

int BoyerMoore::search(
    const std::string& pattern,
    const std::string& text) {
  if (text.size() < pattern.size()) return 0;
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
        unsigned int index =
            static_cast<unsigned int>(text[shift+pattern.size()]);
        shift += std::max(static_cast<int>(pattern.size()) - bad_char_table[index], 
            shift_table[0]);
      } else {
        shift += 1;
      }
    } else {
      unsigned int index = static_cast<unsigned int>(text[shift+cur_char]);
      shift += std::max(std::max(1, cur_char - bad_char_table[index]),
          shift_table[cur_char + 1]);
    }

  }

  return matches;
}

void BoyerMoore::badChar(const std::string& pattern) {

  //Last appearance of a character on the pattern
  for(unsigned int i = 0; i < pattern.size(); i++){
    bad_char_table[static_cast<unsigned int>(pattern[i])] = i;
  }

}

void BoyerMoore::goodSuffix(const std::string& pattern){

  unsigned int i = pattern.size();
  unsigned int j = i + 1;
  border_position[i] = j;
  while(i > 0){
    while(j <= pattern.size() && pattern[i-1] != pattern[j-1]){
      if(shift_table[j] == 0) shift_table[j] = j-i;
      j = border_position[j];
    }
    i--; 
    j--;
    border_position[i] = j;
  }

  j = border_position[0];
  for(i = 0; i <= pattern.size(); i++){
    if(shift_table[i] == 0) shift_table[i] = j;
    if(i == j) j = border_position[j];
  }

}