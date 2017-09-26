#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

class FlagBase {
public:
  virtual bool hasName(const char *)  = 0;
  virtual bool hasShortcut(char)      = 0;
  virtual bool needsValue()           = 0;
  virtual void setValue(const char *) = 0;
  virtual void setValue()             = 0;
  virtual bool isSet()                = 0;
};

template<class T> class Flag : public FlagBase {
private:
  const char *name;
  char shortcut;
  T value;
  bool set;

public:
  Flag(const char *name, char shortcut, const T& value)
      : name(name),
        shortcut(shortcut),
        value(value),
        set(false) {}

  bool hasName(const char *name) {
    return strcmp(this->name, name) == 0;
  }

  bool hasShortcut(char shortcut) {
    return this->shortcut == shortcut;
  }

  bool needsValue() {
    return true;
  }

  void setValue(const char *arg) {
    std::stringstream ss(arg);
    ss >> this->value;
    this->set = true;
  }

  void setValue() {}

  bool isSet() {
    return this->set;
  }

  T getValue() {
    return this->value;
  }
};
template<> bool Flag<bool>::needsValue() {
  return false; 
}
template<> void Flag<bool>::setValue() {
  this->value = true;
  this->set = true;
}

class Flags {
private:
  std::vector<FlagBase*> flags;
  std::vector<std::string> args;

public:
  void addFlag(FlagBase* flag) {
    flags.push_back(flag);
  }

  FlagBase *findByName(const char *name) {
    for (FlagBase *flag : flags) {
      if (flag->hasName(name)) {
        return flag;
      }
    }
    return nullptr;
  }

  FlagBase *findByShortcut(char shortcut) {
    for (FlagBase *flag : flags) {
      if (flag->hasShortcut(shortcut)) {
        return flag;
      }
    }
    return nullptr;
  }

  void parse(int argc, char *argv[]) {
    args.clear();

    for (int i = 1; i < argc; i++) {
      const char *arg = argv[i];
      if (arg[0] != '-') {
        args.push_back(arg);
        continue;
      }
      if (arg[1] == '\0') continue;

      FlagBase *flag = nullptr;
      if (arg[1] == '-') {
        flag = findByName(arg + 2);
      } else {
        // TODO(bolado): Handle multiple options.
        flag = findByShortcut(arg[1]);
      }

      if (flag == nullptr) {
        // TODO(bolado): Report invalid option.
        continue;
      }

      if (flag->needsValue()) {
        bool hasValue = true;
        hasValue = hasValue && i < argc - 1;
        if (!hasValue) {
          // TODO(bolado): Report missing value.
          continue;
        }
        flag->setValue(argv[++i]);
      } else {
        flag->setValue();
      }
    }
  }

  const std::vector<std::string>& getArgs() {
    return args;
  }
} FLAGS;

Flag<int>         FLAG_EDIT     ("edit", 'e', 0);
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

  std::cout << FLAG_EDIT.getValue() << std::endl;
}
