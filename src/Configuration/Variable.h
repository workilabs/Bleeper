#pragma once
#include "Helpers/utils.h"
#include "StringConvertibleVariable.h"

template<class ValueT>
class Variable: public StringConvertibleVariable {
public:
  ValueT* value;

  Variable(String key, ValueT* value, bool isPersistent): StringConvertibleVariable(value, key, isPersistent) {
    this->value = value;
  }

  template<class T>
  T* addTo(std::vector<StringConvertibleVariable*>& bag) {
    bag.push_back(this);
    return (T*) this;
  }

  virtual bool isPersistentVariable() {
    return false;
  }

  virtual String getAsString() = 0;
  virtual void setFromString(const String &value) = 0;

};

class IntVariable: public Variable<int> {
public:
  IntVariable(String key, int* value, bool isPersistent): Variable<int>(key, value, isPersistent) {}

  virtual String getAsString() {
    return String(*value);
  }

  virtual void setFromString(const String &stringValue) {
    *value = stringValue.toInt();
  }

};

class FloatVariable: public Variable<float> {
public:
  FloatVariable(String key, float* value, bool isPersistent): Variable<float>(key, value, isPersistent) {}

  virtual String getAsString() {
    return String(*value);
  }

  virtual void setFromString(const String &stringValue) {
    *value = stringValue.toFloat();
  }

};

class StringVariable: public Variable<String> {
public:
  StringVariable(String key, String* value, bool isPersistent): Variable<String>(key, value, isPersistent) {}

  virtual String getAsString() {
    return *value;
  }

  virtual void setFromString(const String &stringValue) {
    *value = stringValue;
  }

};

#define SetterOfType(T) void (*SetterPtr)(T* intance, const String& value);
#define GetterOfType(T) String (*GetterPtr)(T* intance);

template<class T>
class GenericVariable: public Variable<T> {
public:
    typedef SetterOfType(T);
    typedef GetterOfType(T);
    SetterPtr setter;
    GetterPtr getter;

    GenericVariable(String key, T* value, bool isPersistent, SetterPtr setter, GetterPtr getter): Variable<T>(key, value, isPersistent) {
      this->setter = setter;
      this->getter = getter;
    }

    virtual String getAsString() {
      return getter(this->value);
    }

    virtual void setFromString(const String &stringValue) {
      setter(this->value, stringValue);
    }

};
