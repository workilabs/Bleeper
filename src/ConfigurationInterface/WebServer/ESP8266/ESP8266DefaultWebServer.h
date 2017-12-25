#pragma once

#ifdef ESP8266

#include "Arduino.h"
#include <ESP8266WebServer.h>
#include "ConfigurationInterface/WebServer/WebServer.h"

class ESP8266DefaultWebServer: public WebServer {
protected:
  ESP8266WebServer* server;
  void handleRoot();
  void handleScript();
  void handleStyle();
  void handleSave();
public:
  ESP8266DefaultWebServer(int port);
  virtual void init();
  virtual void handle();
};

#endif // ESP8366
