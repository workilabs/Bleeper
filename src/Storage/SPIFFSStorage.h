#pragma once
#include "Bleeper/BleeperClass.h"
#include "Helpers/Logger.h"
#include "Helpers/utils.h"

#define CONFIGS_FILE "/bleeperVars.bpr"

#ifdef ESP8266
#include "FS.h"
#elif ESP32
#include "SPIFFS.h"
#endif

class SPIFFSStorage: public Storage {
public:
  void init() {
    SPIFFS.begin();
    if (!SPIFFS.exists(CONFIGS_FILE)) {
      SPIFFS.format();
    }
  }

  void persist() {
    File f = SPIFFS.open(CONFIGS_FILE, "w");
    if (!f) {
      f.close();
      return;
    }
    std::vector<String> persistentVars = Bleeper.configuration.getAsDictionary(true).toStrings();
    for(auto const & s: persistentVars) {
      f.print(s);
      f.write(0);
    }
    f.close();
  }

  void load() {
    File f = SPIFFS.open(CONFIGS_FILE, "r");
    if (!f) {
      f.close();
      persist();
      return;
    }
    std::vector<String> storedVars;
    while (f.available()) {
      auto readString = f.readStringUntil('\0');
      storedVars.push_back(readString);
    }
    Bleeper.configuration.setFromDictionary(ConfigurationDictionary(storedVars));
    f.close();
  }

};
