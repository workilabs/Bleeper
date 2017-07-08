#include "ConfigMap.h"

ConfigMap::ConfigMap() {}

void ConfigMap::add(VariableAddress address, StringConvertibleVariable* variable) {
  addressMap[address] = variable;
  keyMap[variable->getFullKey()] = variable;
  variables.push_back(variable);
}
