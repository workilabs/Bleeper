#include "ConfigurationInterface/WebServer/WebServer.h"
#include "Configuration/ConfigurationDictionary.h"
#include "Bleeper/BleeperClass.h"
#include "Helpers/Logger.h"
#include "ConfigurationInterface/WebServer/WebPage.h"

WebServer::WebServer(int port) {
  this->port = port;
}

String WebServer::buildPage(const std::vector<StringConvertibleVariable*> & vars) {
  Log("Page requested");
  String first = "<!DOCTYPE html><title>Bleeper</title><meta content=\"width=device-width,user-scalable=no\"name=viewport><link href=style rel=stylesheet><link rel=\"stylesheet\" href=\"https://fonts.googleapis.com/css?family=Righteous\"><script src=script></script><div id=cf><h1>Bleeper</h1>";
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

void WebServer::saveValues(const std::map<String, String> & args) {
  if (args.size() == 0) return;
  ConfigurationDictionary params;
  for(const auto & arg: args) {
    params[arg.first] = arg.second;
  }
  Bleeper.configuration.setFromDictionary(params);
  Bleeper.storage.persist();
  Log("Configs saved!");
}

const char* WebServer::getJS() {
  return JS;
}

const char* WebServer::getStyle() {
  return CSS;
}
