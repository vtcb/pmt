#include <cstring>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

class FlagBase {
public:
  virtual bool hasName(const char *)  = 0;
  virtual bool hasShortcut(char)      = 0;
  virtual bool needsValue()           = 0;
  virtual void setValue(const char *) = 0;
  virtual void setValue()             = 0;
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
    for (int i = 0; i < argc; i++) {
      const char *arg = argv[i];
      if (arg[0] != '-') continue;
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

int main(int argc, char *argv[]) {
  initFlags();
  FLAGS.parse(argc, argv);
  std::cout << FLAG_EDIT.getValue() << std::endl;
}
