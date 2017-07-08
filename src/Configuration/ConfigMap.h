#pragma once
#include "StringConvertibleVariable.h"
#include "Configuration/ConfigurationDictionary.h"
#include <map>
#include <vector>

typedef const void* VariableAddress;

class ConfigMap {
protected:
  std::map<VariableAddress, StringConvertibleVariable*> addressMap;
  std::map<String, StringConvertibleVariable*> keyMap;
  std::vector<StringConvertibleVariable*> variables;
public:
  ConfigMap();
  void add(VariableAddress address, StringConvertibleVariable* variable);
};
