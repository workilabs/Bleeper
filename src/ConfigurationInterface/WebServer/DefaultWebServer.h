#pragma once
#include "Arduino.h"
#include <ESP8266WebServer.h>
#include "ConfigurationInterface/WebServer/WebServer.h"

class DefaultWebServer: public WebServer {
private:
  ESP8266WebServer* server;
  String buildPage();
  void handleRoot();
  void handleScript();
  void handleStyle();
  void handleSave();
public:
  DefaultWebServer(int port);
  void init();
  void handle();
};
