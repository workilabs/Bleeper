#pragma once
#include "Arduino.h"
class BaseConfiguration;

class StringConvertibleVariable {
protected:
  String key;
  String fullKey;
  void* value;
  bool isPersistent;
public:
  StringConvertibleVariable(void* value, String key, bool isPersistent);
  bool isPersistentVariable();
  virtual String getAsString() = 0;
  virtual void setFromString(const String &value) = 0;
  String getKey();
  void* getMemoryAddress();
  void setFullKey(const String fullKey);
  String getFullKey();

};
