#include "Configuration/ConfigurationDictionary.h"
#include "Helpers/utils.h"
#include "Helpers/macros.h"

ConfigurationDictionary::ConfigurationDictionary() {};

ConfigurationDictionary::ConfigurationDictionary(const std::vector<String> & strings) {
  guard(strings.size() > 0, return);
  for(auto p = 0; p < strings.size() - 1; p += 2) {
    (*this)[strings[p]] = strings[p + 1];
  }
}

void ConfigurationDictionary::append(ConfigurationDictionary dict) {
  insert(dict.begin(), dict.end());
}

std::vector<String> ConfigurationDictionary::toStrings() {
  std::vector<String> result;
  for(auto const& pair: *this) {
    result.push_back(pair.first);
    result.push_back(pair.second);
  }
  return result;
}
