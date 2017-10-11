#include "search_algorithm.h"

#include <string>

SearchAlgorithm::SearchAlgorithm(SearchMode mode, int max_error)
    : mode(mode), matches(0), line_matches(0), max_error(max_error) {}

int SearchAlgorithm::getCount() {
  return this->line_matches;
}

int SearchAlgorithm::getMatches() {
  return this->matches;
}

int SearchAlgorithm::getLineMatches() {
  return this->line_matches;
}

void SearchAlgorithm::output(const std::string& line, int matches) {
  switch (this->mode) {
    case SearchMode::COUNT:
      this->matches += matches;
      this->line_matches += matches > 0;
      break;
    case SearchMode::PRINT:
      if (matches > 0) {
        std::cout << line << std::endl;
      }
      break;
  }
}

int SearchAlgorithm::getMaxError() {
  return max_error;
}
