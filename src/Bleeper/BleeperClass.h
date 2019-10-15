#pragma once
#include "Storage/Storage.h"
#include "Configuration/RootConfiguration.h"
#include "Connectivity/Connection.h"
#include "Configuration/ConfigurationDictionary.h"
#include "ConfigurationInterface/ConfigurationInterface.h"
#include "Bleeper/Initable.h"

#define Bleeper (*BleeperClass::shared())

class BleeperClass: public Initable {
private:
  static BleeperClass* sharedInstance;
  BleeperClass();

  struct UserProperties {
    Storage* storage;
    RootConfiguration* rootConfig;
    std::vector<ConfigurationInterface*> interfaces;
    Connection* connection;
  } userProperties;

public:
  static BleeperClass* shared();
  void handle();
  void init();
  void init(bool loadFromStorage);
  BleeperClass& verbose();
  BleeperClass& verbose(int baudRate);

  class Chainable {
  public:
    BleeperClass& done() {
      return Bleeper;
    }
  };

  class ConfigurationFunctions: public Chainable {
  public:
    ConfigurationFunctions& set(RootConfiguration*);
    ConfigurationFunctions& addObserver(ConfigurationObserver* observer, std::set<VariableAddress> filter = std::set<VariableAddress>());
    RootConfiguration* get();
    ConfigurationDictionary getAsDictionary(bool onlyPersistent = false);
    const std::vector<StringConvertibleVariable*>& getVariables();
    void enableObservers(bool);
    void setFromDictionary(const ConfigurationDictionary&);
  } configuration;

  class ConnectionFunctions: public Chainable {
  public:
    ConnectionFunctions& set(Connection*);
    Connection* get();
    ConnectionFunctions& setMultipleConnections(std::vector<Connection*> connections);
    ConnectionFunctions& setSingleConnectionFromPriorityList(std::vector<Connection*> connections);
  } connection;

  class StorageFunctions: public Chainable {
  public:
    StorageFunctions& set(Storage*);
    StorageFunctions& setDefault();
    StorageFunctions& persist();
  } storage;

  class ConfigurationInterfaceFunctions: public Chainable {
  public:
    ConfigurationInterfaceFunctions& add(ConfigurationInterface*);
    ConfigurationInterfaceFunctions& addDefaultWebServer();
  } configurationInterface;

};
