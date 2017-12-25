#include "Bleeper.h"

class Network: public Configuration {
public:
  stringVar(ip, "localhost");
  intVar(port, 506);
};

class WifiConfig: public Configuration {
public:
  persistentStringVar(ssid, "ssid");
  persistentStringVar(password, "password");
  subconfig(Network, network);
};

class Config: public RootConfiguration {
public:
  floatVar(floatValue, 0);

  var(unsigned int, time, 25,
  {
    time = timeString.toInt();
  },
  {
    timeString = String(time);
  });

  subconfig(WifiConfig, wifi);
} C;

class MyObserver: public ConfigurationObserver {
public:
  void onConfigurationChanged(const ConfigurationPropertyChange value) {
    Serial.println("Configuration " + value.key + " changed from " + value.oldValue + " to " + value.newValue);
  }
};

void setup() {

  Bleeper
    .verbose()
    .configuration
      .set(&C)
      .addObserver(new MyObserver(), {&C.wifi.network.port})
      .done()
    .configurationInterface
      .addDefaultWebServer()
      .done()
    .connection
      .setSingleConnectionFromPriorityList({
          new Wifi(&C.wifi.ssid, &C.wifi.password),
          new AP()
      })
      .done()
    .storage
      .setDefault()
      .done()
    .init();
}

void loop() {

  Bleeper.handle();

}
