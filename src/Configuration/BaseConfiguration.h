#pragma once
#include "Configuration/ConfigurationDictionary.h"
#include "Variable.h"
#include "StringConvertibleVariable.h"
#include "Configuration/ConfigMap.h"

class BaseConfiguration {
protected:
  String prefix;
  std::vector<StringConvertibleVariable*> vars;
  std::vector<BaseConfiguration*> subConfigs;

  template <typename T> void add(Variable<T>& var) {
    vars.push_back(&var);
  }

  void fillConfigMap(String cumulativePrefix, ConfigMap* map) {
      for(StringConvertibleVariable* variable: vars) {
        auto prefix = cumulativePrefix;
        auto varFullKey = (prefix != "") ? prefix + "." + variable->getKey() : variable->getKey();
        variable->setFullKey(varFullKey);
        map->add(variable->getMemoryAddress(), variable);
      }
      for(BaseConfiguration* subConfig: subConfigs) {
        auto cumulative = (cumulativePrefix != "") ? cumulativePrefix + "." + subConfig->prefix: subConfig->prefix;
        subConfig->fillConfigMap(cumulative, map);
      }
  }

public:
  BaseConfiguration() {}

  String getPrefix() {
    return prefix;
  }

  void fillConfigMap(ConfigMap* map) {
      fillConfigMap("", map);
  }

  template <typename T>
  T* addTo(std::vector<BaseConfiguration*>& subConfigs) {
    subConfigs.push_back(this);
    return (T*)this;
  }

  template <typename T>
  T* withPrefix(String prefix) {
    this->prefix = prefix;
    return (T*)this;
  }

};
