#pragma once
#include "Arduino.h"

#define Log(msg) Logger::print(msg)

class Logger {
public:
  static bool verbose;
  static bool serialInitialized;
  static void print(String msg) {
    if (!serialInitialized) {
      Serial.begin(115200);
      while (!Serial) yield();
      serialInitialized = true;
    }
    if (verbose) {
      Serial.println("[Bleeper]: " + msg);
    }
  }
};
