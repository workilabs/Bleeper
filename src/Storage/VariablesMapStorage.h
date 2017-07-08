#pragma once
#include "Bleeper/BleeperClass.h"
#include "Storage/EEPROMHelper.h"

class VariablesMapStorage: public Storage {
private:
  EEPROMHelper eeprom;
public:
  void init() {

  }

  void persist() {
    std::vector<String> persistentVars = Bleeper.configuration.getAsDictionary(true).toStrings();
    eeprom.writeStrings(persistentVars);
  }

  void load() {
    std::vector<String> storedVars = eeprom.readStrings();
    if (storedVars.size() == 0) {
      persist();
    } else {
      Bleeper.configuration.setFromDictionary(ConfigurationDictionary(storedVars));
    }
  }

};
