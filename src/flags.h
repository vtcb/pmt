#ifndef PMT_FLAGS_H
#define PMT_FLAGS_H

#include <string>
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
  Flag(const char *name, char shortcut, const T& value);
  bool hasName(const char *name);
  bool hasShortcut(char shortcut);
  bool needsValue();
  void setValue(const char *arg);
  void setValue();
  bool isSet();
  T getValue();
};

class Flags {
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

#endif /* PMT_FLAGS_H */