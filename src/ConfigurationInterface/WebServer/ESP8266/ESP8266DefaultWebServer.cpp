#ifdef ESP8266

#include "Bleeper/BleeperClass.h"
#include "ConfigurationInterface/WebServer/ESP8266/ESP8266DefaultWebServer.h"
#include <ESP8266mDNS.h>
#include <functional>
#include <map>
#include "Helpers/Logger.h"

ESP8266DefaultWebServer::ESP8266DefaultWebServer(int port): WebServer(port) {
  server = NULL;
}

void ESP8266DefaultWebServer::init() {
  server = new ESP8266WebServer(port);
  server->on(
    "/", std::bind(&ESP8266DefaultWebServer::handleRoot, this)
  );
  server->on(
    "/save", HTTP_POST,
    std::bind(&ESP8266DefaultWebServer::handleSave, this)
  );
  server->on(
    "/script", std::bind(&ESP8266DefaultWebServer::handleScript, this)
  );
  server->on(
    "/style", std::bind(&ESP8266DefaultWebServer::handleStyle, this)
  );
  server->begin();
}

void ESP8266DefaultWebServer::handle(){
  server->handleClient();
}

void ESP8266DefaultWebServer::handleRoot(){
  server->send(HTTP_STATUS_OK, CONTENT_TYPE_HTML, buildPage(Bleeper.configuration.getVariables()));
}

void ESP8266DefaultWebServer::handleScript(){
  server->send_P(HTTP_STATUS_OK, CONTENT_TYPE_JS, getJS());
}

void ESP8266DefaultWebServer::handleStyle(){
  server->send_P(HTTP_STATUS_OK, CONTENT_TYPE_CSS, getStyle());
}

void ESP8266DefaultWebServer::handleSave(){
  server->send(HTTP_STATUS_OK, CONTENT_TYPE_HTML, "");
  std::map<String, String> values;
  for(auto i = 0; i < server->args(); i++) {
    values[server->argName(i)] = server->arg(i);
  }
  saveValues(values);
}

#endif // ESP8266
