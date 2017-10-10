#include "search_algorithm.h"

#include <string>

SearchAlgorithm::SearchAlgorithm(SearchMode mode, int max_error)
    : mode(mode), count(0), max_error(max_error) {}

int SearchAlgorithm::getCount() {
  return this->count;
}

void SearchAlgorithm::output(const std::string& line, int matches) {
  switch (this->mode) {
    case SearchMode::COUNT:
      this->count += matches;
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
