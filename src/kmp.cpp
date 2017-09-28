#include "kmp.h"

#include <fstream>
#include <string>
#include <vector>

#include "search_algorithm.h"

KMP::KMP(SearchMode mode) : SearchAlgorithm(mode) {}

void KMP::search(
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

void KMP::search(std::vector<std::string> pattern_list, std::string text) {
  int matches = 0;
  for (std::string pattern : pattern_list) {
    table.assign(pattern.size(), 0);
    kmp_table(pattern);
    matches += search(pattern, text);
  }
  output(text, matches);
}

int KMP::search(std::string pattern, std::string text) {
  int matches = 0;
  int current_match = 0;
  int current_char = 0;

  while(current_match + current_char < text.size()){
    if(pattern[current_char] == text[current_match + current_char]){
      current_char++;
      if(current_char == pattern.size()){
        matches++;
      }
    }else{
      if(table[current_char] > -1){
        current_match += current_char - table[current_char];
        current_char = table[current_char];
      }else{
        current_match += current_char + 1;
        current_char = 0;
      }
    }

  }
  
  return matches;
}

void KMP::kmp_table(std::string pattern){
  int position = 1;
  int candidate = 0;
  table[0] = -1;

  while (position < pattern.size()){
    if (pattern[position] == pattern[candidate]){
      table[position] = table[candidate];
    }else{
      table[position] = candidate;
      candidate = table[candidate];
      while(candidate >= 0 && pattern[position]){
        candidate = table[candidate];
      }
    }
    position++;
    candidate++;
  }
  table[position] = candidate;

}
