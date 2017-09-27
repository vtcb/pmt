#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "flags.h"
#include "naive.h"

Flags FLAGS;

Flag<int>         FLAG_EDIT     ("edit",      'e', 0);
Flag<std::string> FLAG_PATTERN  ("pattern",   'p', "");
Flag<std::string> FLAG_ALGORITHM("algorithm", 'a', "");
Flag<bool>        FLAG_COUNT    ("count",     'c', false);
Flag<bool>        FLAG_HELP     ("help",      'h', false);

void initFlags() {
  FLAGS.addFlag(&FLAG_EDIT);
  FLAGS.addFlag(&FLAG_PATTERN);
  FLAGS.addFlag(&FLAG_ALGORITHM);
  FLAGS.addFlag(&FLAG_COUNT);
  FLAGS.addFlag(&FLAG_HELP);
}

class InputParser {
public:
  static std::vector<std::string> patternList() {
    std::vector<std::string> pattern_list;
    if (FLAG_PATTERN.isSet()) {
      std::ifstream pattern_file(FLAG_PATTERN.getValue());
      std::string line;
      while (std::getline(pattern_file, line)) {
        pattern_list.push_back(line);
      }
    } else {
      pattern_list.push_back(FLAGS.getArgs()[0]);
    }
    return pattern_list;
  }

  static std::vector<std::string> textfileList() {
    std::vector<std::string> textfile_list;
    std::vector<std::string> args = FLAGS.getArgs();
    for (int i = FLAG_PATTERN.isSet() ? 0 : 1; i < args.size(); i++) {
      textfile_list.push_back(args[i]);
    }
    return textfile_list;
  }

  static SearchMode searchMode() {
    return FLAG_COUNT.getValue() ? SearchMode::COUNT : SearchMode::PRINT;
  }

  static SearchAlgorithm* algorithm(SearchMode search_mode) {
    if (!FLAG_ALGORITHM.isSet()) {
      // Choose
      return new Naive(search_mode);
    }

    if (FLAG_ALGORITHM.getValue() == "brute-force") {
      return new Naive(search_mode);
    }

    return nullptr;
  }
};

void printHelp() {
  // TODO(bolado): Write help
  std::cout << "Help me, Obi-Wan Kenobi. You're my only hope." << std::endl;
}

int main(int argc, char *argv[]) {
  std::ios_base::sync_with_stdio(false);
  
  initFlags();
  FLAGS.parse(argc, argv);

  if (FLAG_HELP.getValue()) {
    printHelp();
    return 0;
  }

  std::vector<std::string> pattern_list  = InputParser::patternList();
  std::vector<std::string> textfile_list = InputParser::textfileList();
  SearchMode               search_mode   = InputParser::searchMode();
  SearchAlgorithm          *algorithm    = InputParser::algorithm(search_mode);

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
