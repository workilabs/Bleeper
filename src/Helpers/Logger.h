#pragma once
#include "Arduino.h"

#define Log(msg) Logger::print(msg)

class Logger {
public:
  static bool verbose;
  static bool serialInitialized;
  static int  baudRate;
  static void print(String msg) {
    if (!serialInitialized) {
      Serial.begin(baudRate);
      while (!Serial) yield();
      serialInitialized = true;
    }
    if (verbose) {
      Serial.println("[Bleeper]: " + msg);
    }
  }
};
