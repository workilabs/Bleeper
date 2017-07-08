#pragma once
#include "BaseConfiguration.h"
#include "Observers/Observable.h"
#include "Observers/ConfigurationObserver.h"
#include "Bleeper/Initable.h"

class RootConfiguration:
  public BaseConfiguration,
  public Observable<ConfigurationObserver>,
  public ConfigMap,
  public Initable {
protected:

  virtual void notifyObserversOfChange(VariableAddress address, const String & key, const String oldValue, const String newValue) {
    if (oldValue == newValue)
      return;
    for(ConfigurationObserver* o: observers) {
      if (o->isInterestedIn(address))
        o->onConfigurationChanged({.key = key, .oldValue = oldValue, .newValue = newValue});
    }
  }

public:

  virtual void init() {
    fillConfigMap(this);
  }

  bool isAddressValid(VariableAddress address) {
    return addressMap.find(address) != addressMap.end();
  }

  StringConvertibleVariable* getVariableForAddress(VariableAddress address) {
    return addressMap[address];
  }

  ConfigurationDictionary getAsDictionary(bool onlyPersistent) {
    ConfigurationDictionary result;
    for(auto const &value : addressMap) {
      if (!onlyPersistent || value.second->isPersistentVariable()) {
        result[value.second->getFullKey()] = value.second->getAsString();
      }
    }
    return result;
  }

  void setFromDictionary(const ConfigurationDictionary& dict) {
    for(auto const &pair : dict) {
      std::map<String, StringConvertibleVariable*>::iterator it = keyMap.find(pair.first);
      if (it != keyMap.end()) {
        auto oldValue = it->second->getAsString();
        it->second->setFromString(pair.second);
        notifyObserversOfChange(it->second->getMemoryAddress(), pair.first, oldValue, it->second->getAsString());
      }
    }
  }

  const std::vector<StringConvertibleVariable*>& getVariables() {
    return variables;
  }

};
