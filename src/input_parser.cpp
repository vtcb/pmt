#include "input_parser.h"

#include <algorithm>
#include <fstream>
#include <locale>
#include <set>
#include <sstream>

Flag<int>         FLAG_EDIT     ("edit",      'e', 0);
Flag<std::string> FLAG_PATTERN  ("pattern",   'p', "");
Flag<std::string> FLAG_ALGORITHM("algorithm", 'a', "");
Flag<bool>        FLAG_COUNT    ("count",     'c', false);
Flag<bool>        FLAG_HELP     ("help",      'h', false);

void InputParser::parse(int argc, char *argv[]) {
  FLAG_PARSER.addFlag(&FLAG_EDIT);
  FLAG_PARSER.addFlag(&FLAG_PATTERN);
  FLAG_PARSER.addFlag(&FLAG_ALGORITHM);
  FLAG_PARSER.addFlag(&FLAG_COUNT);
  FLAG_PARSER.addFlag(&FLAG_HELP);
  FLAG_PARSER.parse(argc, argv);
}

bool InputParser::help() {
  return FLAG_HELP.getValue();
}

std::vector<std::string> InputParser::patternList() {
  std::vector<std::string> pattern_list;
  if (FLAG_PATTERN.isSet()) {
    std::ifstream pattern_file(FLAG_PATTERN.getValue());
    std::string line;
    while (std::getline(pattern_file, line)) {
      pattern_list.push_back(line);
    }
  } else {
    pattern_list.push_back(FLAG_PARSER.getArgs()[0]);
  }
  return pattern_list;
}

std::vector<std::string> InputParser::textfileList() {
  std::vector<std::string> textfile_list;
  std::vector<std::string> args = FLAG_PARSER.getArgs();
  for (int i = FLAG_PATTERN.isSet() ? 0 : 1; i < args.size(); i++) {
    textfile_list.push_back(args[i]);
  }
  return textfile_list;
}

SearchMode InputParser::searchMode() {
  return FLAG_COUNT.getValue() ? SearchMode::COUNT : SearchMode::PRINT;
}

SearchAlgorithm* InputParser::algorithm(SearchMode search_mode) {
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