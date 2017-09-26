#include "flags.h"

#include <cstring>
#include <string>
#include <sstream>
#include <vector>

template<class T> Flag<T>::Flag(const char *name, char shortcut, const T& value)
    : name(name),
      shortcut(shortcut),
      value(value),
      set(false) {}

template<class T> bool Flag<T>::hasName(const char *name) {
  return strcmp(this->name, name) == 0;
}

template<class T> bool Flag<T>::hasShortcut(char shortcut) {
  return this->shortcut == shortcut;
}

template<class T> bool Flag<T>::needsValue() {
  return true;
}

template<class T> void Flag<T>::setValue(const char *arg) {
  std::stringstream ss(arg);
  ss >> this->value;
  this->set = true;
}

template<class T> void Flag<T>::setValue() {}

template<class T> bool Flag<T>::isSet() {
  return this->set;
}

template<class T> T Flag<T>::getValue() {
  return this->value;
}

template<> bool Flag<bool>::needsValue() {
  return false; 
}

template<> void Flag<bool>::setValue() {
  this->value = true;
  this->set = true;
}

template class Flag<int>;
template class Flag<std::string>;
template class Flag<bool>;

void Flags::addFlag(FlagBase* flag) {
  flags.push_back(flag);
}

FlagBase *Flags::findByName(const char *name) {
  for (FlagBase *flag : flags) {
    if (flag->hasName(name)) {
      return flag;
    }
  }
  return nullptr;
}

FlagBase *Flags::findByShortcut(char shortcut) {
  for (FlagBase *flag : flags) {
    if (flag->hasShortcut(shortcut)) {
      return flag;
    }
  }
  return nullptr;
}

void Flags::parse(int argc, char *argv[]) {
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

const std::vector<std::string>& Flags::getArgs() {
  return args;
}
