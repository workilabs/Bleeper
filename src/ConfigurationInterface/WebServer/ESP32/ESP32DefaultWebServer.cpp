#ifdef ESP32

#include "ConfigurationInterface/WebServer/ESP32/ESP32DefaultWebServer.h"
#include "Bleeper/BleeperClass.h"
#include "Helpers/Logger.h"
#include <functional>

ESP32DefaultWebServer::ESP32DefaultWebServer(int port): WebServer(port) {
  server = NULL;
}

void ESP32DefaultWebServer::init() {
  server = new WiFiServer(port);
  using std::placeholders::_1;
  using std::placeholders::_2;
  registerRoute(
    GET,
    "/",
    std::bind(&ESP32DefaultWebServer::handleRoot, this, _1, _2)
  );
  registerRoute(
    GET,
    "/script",
    std::bind(&ESP32DefaultWebServer::handleScript, this, _1, _2)
  );
  registerRoute(
    GET,
    "/style",
    std::bind(&ESP32DefaultWebServer::handleStyle, this, _1, _2)
  );
  registerRoute(
    POST,
    "/save",
    std::bind(&ESP32DefaultWebServer::handleSave, this, _1, _2)
  );
}

void ESP32DefaultWebServer::handle(){
  // This server only starts working when
  // some connection is active.
  // It's safe to call it multiple times.
  server->begin();

  WiFiClient client = server->available();
  if (!client) return;
  Log("New client");
  HTTPRequest request;
  while (client.connected()) {
    if (request.isFinished()) {
      handleRequest(request, client);
      break;
    }
    if (client.available()) {
        char c = client.read();
        request.add(c);
    }
  }
  client.stop();
  Log("Client disconnected");
}

void ESP32DefaultWebServer::handleRequest(HTTPRequest & request, WiFiClient & client) {
  RouteHandler* handler = getRequestHandler(request);
  if (!handler)
    handleError(client);

  (*handler)(request, client);
}

void ESP32DefaultWebServer::handleRoot(HTTPRequest &, WiFiClient & client){
  send(client, true, CONTENT_TYPE_HTML, buildPage(Bleeper.configuration.getVariables()).c_str());
}

void ESP32DefaultWebServer::handleScript(HTTPRequest &, WiFiClient & client){
  send(client, true, CONTENT_TYPE_JS, getJS());
}

void ESP32DefaultWebServer::handleStyle(HTTPRequest &, WiFiClient & client){
  send(client, true, CONTENT_TYPE_CSS, getStyle());
}

void ESP32DefaultWebServer::handleSave(HTTPRequest & request, WiFiClient & client){
  send(client, true, "", NULL);
  saveValues(request.getArgs());
}

void ESP32DefaultWebServer::handleError(WiFiClient & client) {
  send(client, false, "", NULL);
}

void ESP32DefaultWebServer::send(WiFiClient & client, bool ok, String contentType, const char* data) {
  client.println(ok ? "HTTP/1.1 200 OK" : "HTTP/1.1 500 Internal Server Error");
  if (contentType != "") client.println("Content-type:" + contentType);
  client.println();
  if (data != NULL) client.print(data);
  client.println();
}

void ESP32DefaultWebServer::registerRoute(HTTPMethod method, String route, RouteHandler handler) {
  router[String(method) + route] = handler;
}

RouteHandler* ESP32DefaultWebServer::getRequestHandler(HTTPRequest & request) {
  auto key = request.getMethod() + request.getRoute();
  if (router.find(key) == router.end())
    return NULL;
  return &router[key];
}

#endif // ESP32
