#include "Bleeper/BleeperClass.h"
#include "Helpers/Logger.h"
#include "Helpers/macros.h"

#ifdef ESP8266
#include <ESP8266WiFi.h>
#elif ESP32
#include <WiFi.h>
#endif

BleeperClass* BleeperClass::sharedInstance = NULL;

BleeperClass::BleeperClass() {
  userProperties.storage = NULL;
  userProperties.rootConfig = NULL;
  userProperties.connection = NULL;
}

BleeperClass* BleeperClass::shared() {
  if (!sharedInstance)
    sharedInstance = new BleeperClass();
  return sharedInstance;
}

void BleeperClass::handle() {
  for(auto interface: userProperties.interfaces) {
    interface->handle();
  }

  if (userProperties.connection) {
    userProperties.connection->handle();
  }

}

BleeperClass& BleeperClass::verbose() {
    Logger::verbose = true;
    return *this;
}

BleeperClass& BleeperClass::verbose(int baudRate) {
  Logger::verbose = true;
  Logger::baudRate = baudRate;
  return *this;
}

void BleeperClass::init() {
  init(true);
}

void BleeperClass::init(bool loadFromStorage) {
  guard(userProperties.rootConfig, return);

  configuration.enableObservers(false);

  userProperties.rootConfig->init();

  if (userProperties.storage) {
    userProperties.storage->init();
    if (loadFromStorage)
      userProperties.storage->load();
  }

  for(auto interface: userProperties.interfaces) {
    interface->init();
  }

  if (userProperties.connection) {
    WiFi.mode(WIFI_OFF);
    userProperties.connection->init();
    userProperties.connection->connect();
  }
  configuration.enableObservers(true);
}
