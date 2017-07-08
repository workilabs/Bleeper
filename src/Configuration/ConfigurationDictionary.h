#pragma once
#include <Arduino.h>
#include <map>
#include <vector>

class ConfigurationDictionary: public std::map<String, String> {
public:
  ConfigurationDictionary();
  ConfigurationDictionary(const std::vector<String> & strings);
  void append(ConfigurationDictionary);
  std::vector<String> toStrings();
};
