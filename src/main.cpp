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

void printHelp() {
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

  std::vector<std::string> pattern_list;
  std::vector<std::string> textfile_list;

  if (FLAG_PATTERN.isSet()) {
    std::ifstream pattern_file(FLAG_PATTERN.getValue());
    std::string line;
    while (std::getline(pattern_file, line)) {
      pattern_list.push_back(line);
    }
  } else {
    pattern_list.push_back(FLAGS.getArgs()[0]);
  }

  for (int i = FLAG_PATTERN.isSet() ? 0 : 1; i < FLAGS.getArgs().size(); i++) {
    textfile_list.push_back(FLAGS.getArgs()[i]);
  }

  SearchAlgorithm *algorithm = new Naive(SearchMode::COUNT);
  algorithm->search(pattern_list, textfile_list);
  (new Naive(SearchMode::PRINT))->search(pattern_list, textfile_list);
  std::cout << algorithm->getCount() << std::endl;
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