#pragma once

#include "ConfigurationInterface/ConfigurationInterface.h"

class WebServer: public ConfigurationInterface {
protected:
  int port;
public:
  WebServer(int port) {
    this->port = port;
  }
  virtual void init() = 0;
  virtual void handle() = 0;
};
