#pragma once
#include <vector>
#include "Bleeper/Initable.h"

class Connection: public Initable {
protected:
  bool triedToConnect;
  bool isExclusiveConnection;
public:
  bool isConnected;
  bool isConnecting;

  Connection();
  virtual void setIsExclusiveConnection(bool is);
  virtual void connect();
  virtual void disconnect();
  virtual void handle() = 0;
  virtual void init() = 0;
  virtual bool connectionDidFail();
  virtual bool connectionDidComplete();
  virtual void retry();
  virtual bool wantsToRetryConnection();
};

class Connections: public Connection {
protected:
  std::vector<Connection*> connections;
public:
  Connections();
  Connections(std::vector<Connection*> connections);
  virtual void handle();
  virtual void init();
  void add(Connection* c);
};

class MultipleConnection: public Connections {
public:
  MultipleConnection(std::vector<Connection*> connections);
  virtual void connect();
  virtual void disconnect();
  virtual void handle();
};

class OneOfMultipleConnection: public Connections {
private:
  int connectionIndex;
  int betterConnectionIndex;
public:
  OneOfMultipleConnection(std::vector<Connection*> connections);
  OneOfMultipleConnection();
  virtual void connect();
  virtual void disconnect();
  void disconnectFromAllExepct(int c);
  virtual void handle();
  virtual void retry();
};
