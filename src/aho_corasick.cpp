#include "aho_corasick.h"

#include "search_algorithm.h"

AhoCorasick::AhoCorasick(SearchMode mode) : SearchAlgorithm(mode) {}

void AhoCorasick::search(
    std::vector<std::string> pattern_list,
    std::vector<std::string> textfile_list) {
}
