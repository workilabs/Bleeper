#pragma once

#include "Connection.h"
#include "Observers/ConfigurationObserver.h"

class Wifi: public Connection, public ConfigurationObserver  {
private:
  String ssid, password;
  String ssidKey;
  bool _wantsToRetryConnection;
  bool firstTime = true;

  VariableAddress ssidAddress;
  VariableAddress passwordAddress;

  void printWifiStatus();
public:
  Wifi(VariableAddress ssidAddress, VariableAddress passwordAddress);
  virtual void init();
  virtual void onConfigurationChanged(const ConfigurationPropertyChange value);
  virtual void connect();
  virtual void disconnect();
  virtual void handle();
  virtual bool wantsToRetryConnection();
  virtual void retry();
};
