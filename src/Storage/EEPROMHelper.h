#pragma once
#include <EEPROM.h>
#include "Arduino.h"
#include "Helpers/Logger.h"

#define MAX_EEPROM_SIZE 4096
#define FORMAT_VALUE 0x55

class EEPROMHelper {
public:

  EEPROMHelper(){
    EEPROM.begin(MAX_EEPROM_SIZE);
    byte v;
    EEPROM.get(0,v);
    if (v != FORMAT_VALUE){
      Log("Initializing EEPROM...");
      EEPROM.write(0,FORMAT_VALUE);
      unsigned short stringsCount = 0;
      EEPROM.put(1, 0);
      for(int i = 3; i < MAX_EEPROM_SIZE; i++)
        EEPROM.write(i, 0);
      Log("Initializing EEPROM...Done!");
    }
    EEPROM.end();
    delay(500);
  };

public:
  std::vector<String> readStrings() {
    EEPROM.begin(MAX_EEPROM_SIZE);
    std::vector<String> result;
    unsigned short stringsCount;
    EEPROM.get(1, stringsCount);
    int addr = 3;
    for(auto s = 0; s < stringsCount; s++) {
      String res = "";
      for(; addr < MAX_EEPROM_SIZE; addr++){
        char r = char(EEPROM.read(addr));
        if (r == '\0')
          break;
        res += String(r);
      }
      addr++;
      result.push_back(res);
    }
    EEPROM.end();
    return result;
  }

  void writeStrings(const std::vector<String> & strings) {
    EEPROM.begin(MAX_EEPROM_SIZE);

    unsigned short stringsCount = strings.size();
    EEPROM.put(1, stringsCount);

    int addr = 3;
    for(auto s: strings) {
      for(int i = 0; addr < MAX_EEPROM_SIZE && i < s.length(); i++, addr++){
        EEPROM.write(addr, s.charAt(i));
      }
      EEPROM.write(addr,'\0');
      addr++;
    }

    EEPROM.end();
    delay(500);
  }

};
