#ifndef PMT_FLAG_PARSER_H
#define PMT_FLAG_PARSER_H

#include <string>
#include <vector>
#include "flag.h"

class FlagParser {
private:
  std::vector<FlagBase*> flags;
  std::vector<std::string> args;

public:
  void addFlag(FlagBase* flag);
  FlagBase *findByName(const char *name);
  FlagBase *findByShortcut(char shortcut);
  void parse(int argc, char *argv[]);
  const std::vector<std::string>& getArgs();
};

#endif /* PMT_FLAG_PARSER_H */