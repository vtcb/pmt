#ifndef PMT_INPUT_PARSER_H
#define PMT_INPUT_PARSER_H

#include <string>
#include <vector>

#include "flag.h"
#include "flag_parser.h"
#include "search_algorithm.h"
#include "search_algorithms.h"

class InputParser {
public:
  void parse(int argc, char *argv[]);
  bool help();
  bool hasOutputFile();
  std::string outputFile();
  std::vector<std::string> patternList();
  std::vector<std::string> textfileList();
  SearchMode searchMode();
  int maxError();
  SearchAlgorithm* algorithm();

private:
  FlagParser FLAG_PARSER;
};

#endif /* PMT_INPUT_PARSER_H */
