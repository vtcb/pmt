#include <cstring>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <locale>
#include <set>
#include <string>
#include <sstream>
#include <vector>

#include "flags.h"
#include "search_algorithms.h"

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
    static const std::set<std::string> _NAIVE =
        {"naive", "brute-force", "bruteforce", "bf"};
    static const std::set<std::string> _KMP =
        {"kmp", "knuth-morris-pratt", "knuthmorrispratt"};
    static const std::set<std::string> _AHO =
        {"aho", "aho-corasick", "ahocorasick", "ac"};

    std::string alias = FLAG_ALGORITHM.getValue();
    std::transform(alias.begin(), alias.end(),alias.begin(), ::towlower);

    static const auto checkAlgorithm =
        [&](std::set<std::string> aliases) -> bool {
      return aliases.count(alias) > 0;
    };

    if (!FLAG_ALGORITHM.isSet()) {
      if (FLAG_EDIT.getValue() == 0) {
        return new Naive(search_mode);
      }
      return nullptr;
    }

    if (checkAlgorithm(_NAIVE)) return new Naive      (search_mode);
    if (checkAlgorithm(_KMP))   return new KMP        (search_mode);
    if (checkAlgorithm(_AHO))   return new AhoCorasick(search_mode);
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
