#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include "flag.h"
#include "flag_parser.h"
#include "input_parser.h"
#include "search_algorithms.h"

void printHelp() {
  // TODO(bolado): Write help
  std::cout << "Help me, Obi-Wan Kenobi. You're my only hope." << std::endl;
}

int main(int argc, char *argv[]) {
  std::ios_base::sync_with_stdio(false);
  
  InputParser input_parser = InputParser();
  input_parser.parse(argc, argv);

  if (input_parser.help()) {
    printHelp();
    return 0;
  }

  std::vector<std::string> pattern_list  = input_parser.patternList();
  std::vector<std::string> textfile_list = input_parser.textfileList();
  SearchMode               search_mode   = input_parser.searchMode();
  SearchAlgorithm          *algorithm    = input_parser.algorithm(search_mode);

  if (pattern_list.empty()) {
    std::cerr << "Pattern list can't be empty." << std::endl;
    // TODO(bolado): Add usage.
    // TODO(bolado): Even for an empty file?
    exit(1);
  }
  if (textfile_list.empty()) {
    std::cerr << "Textfile list can't be empty." << std::endl;
    // TODO(bolado): Add usage.
    exit(1);
  }
  if (algorithm == nullptr) {
    std::cerr << "Algorithm not recognized" << std::endl;
    // TODO(bolado): Add help.
    exit(1);
  }

  switch (search_mode) {
    case SearchMode::COUNT:
      algorithm->search(pattern_list, textfile_list);
      std::cout << algorithm->getCount() << std::endl;
      break;
    case SearchMode::PRINT:
      algorithm->search(pattern_list, textfile_list);
      break;
  }
}

/**
 * Brute force
 * KMP
 * Aho-Corasick
 * Boyer-Moore
 * Sellers
 * Shift-Or
 * Ukkonen
 * Wu-Mamber
 */
