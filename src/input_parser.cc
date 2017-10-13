#include "input_parser.h"

#include <algorithm>
#include <fstream>
#include <locale>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "algorithm_chooser.h"

Flag<int>         FLAG_EDIT     ("edit",      'e', 0);
Flag<std::string> FLAG_PATTERN  ("pattern",   'p', "");
Flag<std::string> FLAG_ALGORITHM("algorithm", 'a', "");
Flag<bool>        FLAG_COUNT    ("count",     'c', false);
Flag<bool>        FLAG_HELP     ("help",      'h', false);
Flag<std::string> FLAG_OUTPUT   ("output",    'o', "");

void InputParser::parse(int argc, char *argv[]) {
  FLAG_PARSER.addFlag(&FLAG_EDIT);
  FLAG_PARSER.addFlag(&FLAG_PATTERN);
  FLAG_PARSER.addFlag(&FLAG_ALGORITHM);
  FLAG_PARSER.addFlag(&FLAG_COUNT);
  FLAG_PARSER.addFlag(&FLAG_HELP);
  FLAG_PARSER.addFlag(&FLAG_OUTPUT);
  FLAG_PARSER.parse(argc, argv);
}

bool InputParser::help() {
  return FLAG_HELP.getValue();
}

bool InputParser::hasOutputFile() {
  return FLAG_OUTPUT.isSet();
}

std::string InputParser::outputFile() {
  return FLAG_OUTPUT.getValue();
}

// TODO(bolado): Handle empty lines
std::vector<std::string> InputParser::patternList() {
  std::vector<std::string> pattern_list;
  if (FLAG_PATTERN.isSet()) {
    std::ifstream pattern_file(FLAG_PATTERN.getValue());
    std::string line;
    while (std::getline(pattern_file, line)) {
      pattern_list.push_back(line);
    }
  } else if (!FLAG_PARSER.getArgs().empty()) {
    pattern_list.push_back(FLAG_PARSER.getArgs()[0]);
  }
  return pattern_list;
}

std::vector<std::string> InputParser::textfileList() {
  std::vector<std::string> textfile_list;
  std::vector<std::string> args = FLAG_PARSER.getArgs();
  for (unsigned int i = FLAG_PATTERN.isSet() ? 0 : 1; i < args.size(); i++) {
    textfile_list.push_back(args[i]);
  }
  return textfile_list;
}

SearchMode InputParser::searchMode() {
  return FLAG_COUNT.getValue() ? SearchMode::COUNT : SearchMode::PRINT;
}

int InputParser::maxError() {
  return FLAG_EDIT.getValue();
}

SearchAlgorithm* InputParser::algorithm() {
  static const std::set<std::string> _NAIVE =
      {"naive", "brute-force", "bruteforce", "bf"};
  static const std::set<std::string> _KMP =
      {"kmp", "knuth-morris-pratt", "knuthmorrispratt"};
  static const std::set<std::string> _AHO =
      {"aho", "aho-corasick", "ahocorasick", "ac"};
  static const std::set<std::string> _BITAP =
      {"bitap", "shift-or", "shift-and", "shiftor", "shiftand", "so"};
  static const std::set<std::string> _BOYER =
      {"boyer", "moore", "boyermoore", "boyer-moore", "bm"};
  static const std::set<std::string> _SELLERS =
      {"sellers", "edit-distance", "editdistance", "se", "ed"};
  static const std::set<std::string> _UKKONEN =
      {"ukkonen", "uk", "u"};

  SearchMode search_mode = InputParser::searchMode();
  int max_error = InputParser::maxError();

  if (!FLAG_ALGORITHM.isSet()) {
    return AlgorithmChooser::choose(patternList(), searchMode(), maxError());
  }

  std::string alias = FLAG_ALGORITHM.getValue();
  std::transform(alias.begin(), alias.end(), alias.begin(), ::towlower);

  static const auto checkAlgorithm =
      [&](std::set<std::string> aliases) -> bool {
    return aliases.count(alias) > 0;
  };

  if (checkAlgorithm(_NAIVE))   return new Naive      (search_mode);
  if (checkAlgorithm(_KMP))     return new KMP        (search_mode);
  if (checkAlgorithm(_AHO))     return new AhoCorasick(search_mode);
  if (checkAlgorithm(_BITAP))   return new Bitap      (search_mode);
  if (checkAlgorithm(_BOYER))   return new BoyerMoore (search_mode);
  if (checkAlgorithm(_SELLERS)) return new Sellers    (search_mode, max_error);
  if (checkAlgorithm(_UKKONEN)) return new Ukkonen    (search_mode, max_error);

  return nullptr;
}
