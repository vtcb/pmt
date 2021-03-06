#ifndef PMT_HELP_H
#define PMT_HELP_H

#include <iostream>

const char *USAGE =
"Usage: pmt [OPTION]... [PATTERN] [TEXTFILE]...\n"
"       pmt [OPTION]... -p [PATTERNFILE] [TEXTFILE]...\n";

// TODO(bolado): Write this.
const char *DESCRIPTION =
"TODO\n";

const char *OPTIONS =
"Options:\n"
"  -h, --help      Display this text\n"
"  -p, --pattern   Specify file to get patterns from\n"
"  -a, --algorithm Specify search algorithm to run\n"
"                  See \"Algorithms\" section for possible values\n"
"  -e, --edit      Specify max error\n"
"  -c, --count     Output only number of matches\n"
"  -o, --output    Specify file to redirect output\n";

// TODO(bolado): Add complexity, approximate matching, multiple patterns etc.
const char *ALGORITHMS =
"Algorithms:\n"
"  Brute Force:\n"
"    Naive implementation of the matching algorithm\n"
"    Values: bf, brute-force, bruteforce, naive\n"
"  KMP:\n"
"    Knuth-Morris-Pratt algorithm\n"
"    Values: kmp, knuth-morris-pratt, knuthmorrispratt\n"
"  Aho Corasick:\n"
"    Aho Corasick algorithm\n"
"    Values: ac, aho, aho-corasick, ahocorasick\n"
"  Bitap:\n"
"    Bitap algorithm\n"
"    Values: so, bitap, shift-or, shift-and, shiftor, shiftand\n"
"  Boyer-Moore:\n"
"    Boyer-Moore algorithm\n"
"    Values: boyer, moore, boyermoore, boyer-moore, bm\n"
"  Sellers:\n"
"    Sellers' algorithm\n"
"    Handles approximate matching\n"
"    Values: se, ed, sellers, edit-distance, editdistance\n"
"  Ukkonen:\n"
"    Ukkonen's algorithm\n"
"    Handles approximate matching\n"
"    Values: u, uk, ukkonen\n";

// TODO(bolado): Handle stdout versus stderr.
class Help {
public:
  static void help() {
    output(USAGE, DESCRIPTION, OPTIONS, ALGORITHMS);
  }

  static void usage() {
    output(USAGE);
  }

  static void options() {
    output(OPTIONS);
  }

  static void algorithms() {
    output(ALGORITHMS);
  }

private:
  template<typename T, typename... Args>
  static void output(T message, Args... args) {
    std::cout << message;
    output(args...);
  }
  template<typename T>
  static void output(T message) {
    std::cout << message;
  }
};

#endif /* PMT_HELP_H */
