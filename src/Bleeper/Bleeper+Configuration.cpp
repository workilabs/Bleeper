#include "Bleeper/BleeperClass.h"
#include "Observers/ConfigurationObserver.h"
#include "Helpers/macros.h"

#define FunctionsContainer BleeperClass::ConfigurationFunctions

FunctionsContainer& FunctionsContainer::addObserver(ConfigurationObserver* observer, std::set<VariableAddress> filter) {
  guard(Bleeper.userProperties.rootConfig != NULL, return *this);
  observer->setFilter(filter);
  Bleeper.userProperties.rootConfig->addObserver(observer);
  return *this;
}

FunctionsContainer& FunctionsContainer::set(RootConfiguration* config) {
  Bleeper.userProperties.rootConfig = config;
  return *this;
}

void FunctionsContainer::setFromDictionary(const ConfigurationDictionary& dict) {
  Bleeper.userProperties.rootConfig->setFromDictionary(dict);
}

ConfigurationDictionary FunctionsContainer::getAsDictionary(bool onlyPersistent) {
  guard(Bleeper.userProperties.rootConfig, return ConfigurationDictionary());
  return Bleeper.userProperties.rootConfig->getAsDictionary(onlyPersistent);
}

RootConfiguration* FunctionsContainer::get() {
  return Bleeper.userProperties.rootConfig;
}

void FunctionsContainer::enableObservers(bool enable) {
  ConfigurationObserver::isEnabled = enable;
}

const std::vector<StringConvertibleVariable*>& FunctionsContainer::getVariables() {
  return Bleeper.userProperties.rootConfig->getVariables();
}
