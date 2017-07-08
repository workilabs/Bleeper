#include "Configuration/StringConvertibleVariable.h"

StringConvertibleVariable::StringConvertibleVariable(void* value, String key, bool isPersistent){
  this->key = key;
  this->value = value;
  this->isPersistent = isPersistent;
}

bool StringConvertibleVariable::isPersistentVariable() {
  return isPersistent;
}

String StringConvertibleVariable::getKey() {
  return key;
}

void* StringConvertibleVariable::getMemoryAddress() {
  return value;
}

void StringConvertibleVariable::setFullKey(const String fullKey) {
  this->fullKey = fullKey;
}

String StringConvertibleVariable::getFullKey() {
  return fullKey;
}
