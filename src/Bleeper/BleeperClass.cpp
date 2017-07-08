#include "Bleeper/BleeperClass.h"
#include "Helpers/Logger.h"
#include "Helpers/macros.h"
#include <ESP8266WiFi.h>

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

void BleeperClass::init() {
  guard(userProperties.rootConfig, return);

  configuration.enableObservers(false);

  userProperties.rootConfig->init();

  if (userProperties.storage) {
    userProperties.storage->init();
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
