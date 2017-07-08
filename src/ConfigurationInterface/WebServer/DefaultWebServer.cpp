#include "ConfigurationInterface/WebServer/DefaultWebServer.h"
#include "Configuration/ConfigurationDictionary.h"
#include <ESP8266mDNS.h>
#include "Bleeper/BleeperClass.h"
#include "ConfigurationInterface/WebServer/WebPage.h"
#include "Helpers/Logger.h"
#include <functional>

DefaultWebServer::DefaultWebServer(int port): WebServer(port) {
  server = NULL;
}

void DefaultWebServer::init() {
  server = new ESP8266WebServer(port);
  server->on(
    "/", std::bind(&DefaultWebServer::handleRoot, this)
  );
  server->on(
    "/save", HTTP_POST,
    std::bind(&DefaultWebServer::handleSave, this)
  );
  server->on(
    "/script", std::bind(&DefaultWebServer::handleScript, this)
  );
  server->on(
    "/style", std::bind(&DefaultWebServer::handleStyle, this)
  );
  server->begin();
  Log("HTTP server started");
}

void DefaultWebServer::handle(){
  server->handleClient();
}

void DefaultWebServer::handleRoot(){
  Log("Page requested!");
  server->send(200, "text/html", buildPage());
}

void DefaultWebServer::handleScript(){
  Log("Script requested!");
  server->send(200, "application/javascript", JS);
}

void DefaultWebServer::handleStyle(){
  Log("Style requested!");
  server->send(200, "text/css", CSS);
}

void DefaultWebServer::handleSave(){
  server->send(200, "text/html", "Ok");

  ConfigurationDictionary params;
  for(int i = 0; i < server->args(); i++){
    params[server->argName(i)] = server->arg(i);
  }

  if (params.size() > 0){
    Log("Configs saved!");
    Bleeper.configuration.setFromDictionary(params);
    Bleeper.storage.persist();
  }

}

String DefaultWebServer::buildPage(){
  String first = "<!DOCTYPE html><title>Bleeper</title><meta content=\"width=device-width,user-scalable=no\"name=viewport><link href=style rel=stylesheet><script src=script></script><div id=cf><h1>Bleeper</h1>";

  auto vars = Bleeper.configuration.getVariables();
  String middle = "";

  for(auto const& v: vars) {
    yield();
    String key = v->getFullKey();
    String value = v->getAsString();
    String classs = v->isPersistentVariable() ? "p" : "";
    middle += "<label class=\"" + classs + "\" for=\"" + key + "\">" + key + "</label>\n";
    middle +=  "<input type=\"text\" id=\"" + key + "\" name=\"" + key + "\" value=\"" + value + "\">\n";
  }

  yield();

  String last = "<button onclick=save() type=button>Save</button></div>";
  return first + middle + last;
}
