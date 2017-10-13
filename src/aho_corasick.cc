#include "aho_corasick.h"

#include "search_algorithm.h"

#include <fstream>
#include <queue>

AhoCorasick::AhoCorasick(SearchMode mode) : SearchAlgorithm(mode) {
  nodes.push_back(AhoNode());
}

void AhoCorasick::search(
    const std::vector<std::string>& pattern_list,
    const std::vector<std::string>& textfile_list) {
  for (std::string pattern : pattern_list) {
    add(pattern);
  }

  activate();

  for (std::string filename : textfile_list) {
    std::ifstream textfile(filename);
    std::string line;
    while (std::getline(textfile, line)) {
      output(line, search(line));
    }
  }
}

void AhoCorasick::add(const std::string& str) {
  int u = 0;
  for (unsigned char ch : str) {
    if (!nodes[u].hasNext(ch)) {
      nodes[u][ch] = nodes.size();
      nodes.push_back(AhoNode());
    }
    u = nodes[u][ch];
  }
  nodes[u].addPattern();
}

void AhoCorasick::activate() {
  std::queue<int> q;
  auto processNode = [&](int u, int fail) {
    nodes[u].setFail(fail);
    q.push(u);
  };

  processNode(0, 0);

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    unsigned char ch = 255;
    do {
      if (!nodes[u].hasNext(ch)) continue;
      int v = nodes[u][ch];
      int dad = u;
      int fail = 0;

      while (dad) {
        dad = nodes[dad].getFail();
        if (nodes[dad].hasNext(ch)) {
          fail = nodes[dad][ch];
          break;
        }
      }
      nodes[v].addPatterns(nodes[fail].getPatterns());

      processNode(v, fail);
    } while (ch--);
  }

  // TODO(bolado): Preprocess edges.
}

void AhoCorasick::traverse(int u, const std::string& s) {
  printf("AHO TRAVERSAL: %02d %02d %02d %s\n",
      u, nodes[u].getFail(), nodes[u].getPatterns(), s.c_str());
  unsigned char ch = 255;
  do {
    if (!nodes[u].hasNext(ch)) continue;
    std::string ds = s;
    ds += ch;
    traverse(nodes[u][ch], ds);
  } while (ch--);
}

int AhoCorasick::search(const std::string& text) {
  int u = 0;
  int matches = 0;
  for (unsigned char ch : text) {
    while (u && !nodes[u].hasNext(ch)) {
      u = nodes[u].getFail();
    }

    if (nodes[u].hasNext(ch)) {
      u = nodes[u][ch];
    }
    matches += nodes[u].getPatterns();
  }
  return matches;
}
