#include "search_algorithm.h"

#include <string>

SearchAlgorithm::SearchAlgorithm(SearchMode mode) : mode(mode), count(0) {}

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

int SearchAlgorithm::getCount() {
  return this->count;
}
