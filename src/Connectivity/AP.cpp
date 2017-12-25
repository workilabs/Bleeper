#include "Connectivity/AP.h"

#ifdef ESP8266
#include <ESP8266WiFi.h>
#elif ESP32
#include <WiFi.h>
#endif

#include "Helpers/Logger.h"

void AP::connect() {
  Connection::connect();

  if (!isExclusiveConnection) {
    #ifdef ESP8266
    WiFi.mode((WiFiMode)(WiFi.getMode() | WIFI_AP));
    #elif ESP32
    WiFi.mode((WiFiMode_t)(WiFi.getMode() | WIFI_AP));
    #endif
  }

  WiFi.softAP("Bleeper");
  Log("AP IP address: " + WiFi.softAPIP().toString());
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
