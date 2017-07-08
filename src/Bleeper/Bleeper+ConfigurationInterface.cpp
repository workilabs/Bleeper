#include "ConfigurationInterface/WebServer/DefaultWebServer.h"
#include "Bleeper/BleeperClass.h"
#include "Helpers/macros.h"

#define FunctionsContainer BleeperClass::ConfigurationInterfaceFunctions

FunctionsContainer& FunctionsContainer::add(ConfigurationInterface* i) {
  Bleeper.userProperties.interfaces.push_back(i);
  return *this;
}

FunctionsContainer& FunctionsContainer::addDefaultWebServer() {
  Bleeper.userProperties.interfaces.push_back(new DefaultWebServer(80));
  return *this;
}
