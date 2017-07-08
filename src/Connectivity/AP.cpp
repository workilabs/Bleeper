#include "Connectivity/AP.h"
#include <ESP8266WiFi.h>
#include "Helpers/Logger.h"

void AP::connect() {
  Connection::connect();

  if (!isExclusiveConnection) {
    WiFi.mode((WiFiMode)(WiFi.getMode() | WIFI_AP));
  }

  WiFi.softAP("Bleeper");
  Log("AP IP address: " + WiFi.softAPIP());
};

void AP::disconnect() {
  Connection::disconnect();
  WiFi.softAPdisconnect(true);
};

void AP::init() {
}

void AP::handle() {
  isConnected = true;
  isConnecting = false;
};
