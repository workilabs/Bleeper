#pragma once
#include "Arduino.h"

#define Log(msg) Logger::print(msg)

class Logger {
public:
  static bool verbose;
  static bool serialInitialized;
  static void print(String msg) {
    if (!Serial && !serialInitialized) {
      Serial.begin(9600);
      while (!Serial) {
        yield();
      }
      serialInitialized = true;
    }
    if (verbose) {
      Serial.println(msg);
    }
  }
};
