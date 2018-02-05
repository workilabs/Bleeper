#ifdef ESP8266
#include "ConfigurationInterface/WebServer/ESP8266/ESP8266DefaultWebServer.h"
#elif ESP32
#include "ConfigurationInterface/WebServer/ESP32/ESP32DefaultWebServer.h"
#endif

#include "Bleeper/BleeperClass.h"
#include "Helpers/macros.h"

#define FunctionsContainer BleeperClass::ConfigurationInterfaceFunctions

FunctionsContainer& FunctionsContainer::add(ConfigurationInterface* i) {
  Bleeper.userProperties.interfaces.push_back(i);
  return *this;
}

FunctionsContainer& FunctionsContainer::addDefaultWebServer() {
  #ifdef ESP8266
  Bleeper.userProperties.interfaces.push_back(new ESP8266DefaultWebServer(80));
  #elif ESP32
  Bleeper.userProperties.interfaces.push_back(new ESP32DefaultWebServer(80));
  #endif
  return *this;
}
