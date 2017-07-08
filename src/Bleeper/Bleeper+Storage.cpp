#include "Bleeper/BleeperClass.h"
#include "Storage/VariablesMapStorage.h"
#include "Helpers/macros.h"

#define FunctionsContainer BleeperClass::StorageFunctions

FunctionsContainer& FunctionsContainer::set(Storage* s) {
  Bleeper.userProperties.storage = s;
  return *this;
}

FunctionsContainer& FunctionsContainer::setDefault() {
  Bleeper.userProperties.storage = new VariablesMapStorage();
  return *this;
}

FunctionsContainer& FunctionsContainer::persist() {
  guard(Bleeper.userProperties.storage, return *this);
  Bleeper.userProperties.storage->persist();
  return *this;
}
