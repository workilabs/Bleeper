#pragma once

#ifdef ESP32

#include "Arduino.h"
#include <WiFiServer.h>
#include "ConfigurationInterface/WebServer/WebServer.h"
#include "ConfigurationInterface/WebServer/ESP32/HTTPRequest.h"
#include <functional>
#include <map>

typedef std::function<void(HTTPRequest & request, WiFiClient &)> RouteHandler;

class ESP32DefaultWebServer: public WebServer {
protected:
  WiFiServer* server;
  std::map<String, RouteHandler> router;
  void handleRequest(HTTPRequest &, WiFiClient &);
  void handleRoot(HTTPRequest &, WiFiClient &);
  void handleScript(HTTPRequest &, WiFiClient &);
  void handleStyle(HTTPRequest &, WiFiClient &);
  void handleSave(HTTPRequest &, WiFiClient &);
  void handleError(WiFiClient &);
  void send(WiFiClient & client, bool ok, String contentType, const char* data);
  void registerRoute(HTTPMethod method, String route, RouteHandler handler);
  RouteHandler* getRequestHandler(HTTPRequest &);
public:
  ESP32DefaultWebServer(int port);
  virtual void init();
  virtual void handle();
};

#endif // ESP32
