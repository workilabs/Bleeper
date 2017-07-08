#include "Connectivity/Wifi.h"
#include <ESP8266WiFi.h>
#include "Bleeper/BleeperClass.h"
#include "Helpers/Logger.h"
#include "Helpers/macros.h"

void Wifi::printWifiStatus() {
  Log("SSID: " + WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  Log("IP Address: " + String(ip));
}

Wifi::Wifi(VariableAddress ssidAddress, VariableAddress passwordAddress) {
  this->ssidAddress = ssidAddress;
  this->passwordAddress = passwordAddress;
}

void Wifi::init() {
  auto c = Bleeper.configuration.get();
  guard(c, return);
  guard(c->isAddressValid(ssidAddress), return);
  guard(c->isAddressValid(passwordAddress), return);

  StringConvertibleVariable* ssid = c->getVariableForAddress(ssidAddress);
  StringConvertibleVariable* password = c->getVariableForAddress(passwordAddress);
  this->ssid = ssid->getAsString();
  ssidKey = ssid->getFullKey();
  this->password = password->getAsString();
  _wantsToRetryConnection = false;
  Bleeper.configuration.addObserver(this, {ssidAddress, passwordAddress});
}

void Wifi::onConfigurationChanged(const ConfigurationPropertyChange value) {
  Log("wifi settings changed...");
  Log("Wifi -> " + value.key + " changed from " + value.oldValue + " to " + value.newValue);
  if (value.key == ssidKey) {
    ssid = value.newValue;
  } else {
    password = value.newValue;
  }
  _wantsToRetryConnection = true;
}

void Wifi::connect() {
  Connection::connect();
  _wantsToRetryConnection = false;
  if (!isExclusiveConnection) {
    WiFi.mode((WiFiMode)(WiFi.getMode() | WIFI_STA));
  }
  WiFi.begin(ssid.c_str(), password.c_str());
};

void Wifi::disconnect() {
  Connection::disconnect();
  WiFi.disconnect(true);
};

void Wifi::handle() {
  auto status = WiFi.status();
  isConnected = (status == WL_CONNECTED);
  isConnecting = !isConnected && (status == WL_DISCONNECTED || status == WL_IDLE_STATUS);
  if (isConnected && firstTime) {
    printWifiStatus();
    firstTime = false;
  }
};

bool Wifi::wantsToRetryConnection() {
  return _wantsToRetryConnection;
}

void Wifi::retry() {
  firstTime = true;
  WiFi.disconnect();
  connect();
}
