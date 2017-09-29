#ifndef PMT_INPUT_PARSER_H
#define PMT_INPUT_PARSER_H

#include "flag.h"
#include "flag_parser.h"
#include "search_algorithm.h"
#include "search_algorithms.h"

class InputParser {
private:
  FlagParser FLAG_PARSER;
public:
  void parse(int argc, char *argv[]);
  bool help();
  std::vector<std::string> patternList();
  std::vector<std::string> textfileList();
  SearchMode searchMode();
  SearchAlgorithm* algorithm(SearchMode search_mode);
};

#endif /* PMT_INPUT_PARSER_H */
