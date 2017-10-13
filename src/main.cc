#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include "flag.h"
#include "flag_parser.h"
#include "help.h"
#include "input_parser.h"
#include "search_algorithms.h"

int main(int argc, char *argv[]) {
  std::ios_base::sync_with_stdio(false);

  InputParser input_parser = InputParser();
  input_parser.parse(argc, argv);

  if (input_parser.help()) {
    Help::help();
    return 0;
  }

  std::vector<std::string> pattern_list  = input_parser.patternList();
  std::vector<std::string> textfile_list = input_parser.textfileList();
  SearchMode               search_mode   = input_parser.searchMode();
  SearchAlgorithm          *algorithm    = input_parser.algorithm();

  if (input_parser.hasOutputFile()) {
    freopen(input_parser.outputFile().c_str(), "w", stdout);
  }

  if (pattern_list.empty()) {
    std::cout << "Pattern list can't be empty." << std::endl;
    // TODO(bolado): Even for an empty file?
    Help::usage();
    exit(1);
  }
  if (textfile_list.empty()) {
    std::cout << "Textfile list can't be empty." << std::endl;
    Help::usage();
    exit(1);
  }
  if (algorithm == nullptr) {
    std::cout << "Algorithm not recognized." << std::endl;
    Help::algorithms();
    exit(1);
  }

  switch (search_mode) {
    case SearchMode::COUNT:
      algorithm->search(pattern_list, textfile_list);
      std::cout << "Lines:   " << algorithm->getCount() << std::endl;
      std::cout << "Matches: " << algorithm->getMatches() << std::endl;
      break;
    case SearchMode::PRINT:
      algorithm->search(pattern_list, textfile_list);
      break;
  }
}

/**
 * Brute force    OK
 * KMP            OK
 * Aho-Corasick   OK
 * Boyer-Moore    OK
 * Sellers        OK
 * Shift-Or       OK
 * Ukkonen        OK
 * Wu-Mamber
 */
