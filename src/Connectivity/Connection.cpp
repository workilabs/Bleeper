#include "Connectivity/Connection.h"
#include "Helpers/Logger.h"

Connection::Connection() {
  triedToConnect = false;
  isExclusiveConnection = false;
}

void Connection::setIsExclusiveConnection(bool is) {
  isExclusiveConnection = is;
}

void Connection::connect() {
  triedToConnect = true;
  isConnecting = true;
}

void Connection::disconnect() {
  triedToConnect = false;
  isConnecting = false;
  isConnected = false;
}

bool Connection::connectionDidFail() {
  return triedToConnect && !isConnected && !isConnecting;
}

bool Connection::connectionDidComplete() {
  return triedToConnect && isConnected && !isConnecting;
}

void Connection::retry() {
  disconnect();
  connect();
}

bool Connection::wantsToRetryConnection() {
  return false;
}

Connections::Connections() {

}

Connections::Connections(std::vector<Connection*> connections) {
  this->connections = connections;
}

void Connections::handle() {};

void Connections::init() {
  for(auto c: connections) {
    c->init();
  }
};

void Connections::add(Connection* c) {
  connections.push_back(c);
}

MultipleConnection::MultipleConnection(std::vector<Connection*> connections) : Connections(connections) {
}

void MultipleConnection::connect() {
  Connections::connect();
  for(Connection* c: connections) {
    c->setIsExclusiveConnection(false);
    c->connect();
  }
}

void MultipleConnection::disconnect() {
  Connections::disconnect();
  for(Connection* c: connections) {
    c->disconnect();
  }
}

void MultipleConnection::handle() {
  bool allConnectionsConnected = true;
  for(Connection* c: connections) {
    if (c->wantsToRetryConnection()) {
      Log("retrying connection");
      c->connect();
    }
    c->handle();
    isConnecting = isConnecting || c->isConnecting;
    allConnectionsConnected = allConnectionsConnected && c->isConnected;
  }
  isConnected = allConnectionsConnected;
}

OneOfMultipleConnection::OneOfMultipleConnection(std::vector<Connection*> connections) : Connections(connections) {
  connectionIndex = 0;
  betterConnectionIndex = -1;
}

OneOfMultipleConnection::OneOfMultipleConnection() {
  connectionIndex = 0;
  betterConnectionIndex = -1;
}

void OneOfMultipleConnection::connect() {
  Connections::connect();
  connections[connectionIndex]->connect();
}

void OneOfMultipleConnection::disconnect() {
  Connections::disconnect();
  for(Connection* c: connections) {
    c->disconnect();
  }
}

void OneOfMultipleConnection::disconnectFromAllExepct(int c) {
  for(auto i = 0; i < connections.size(); i++) {
    if (i != c)
      connections[i]->disconnect();
  }
}

void OneOfMultipleConnection::handle() {
  if (connections[connectionIndex]->wantsToRetryConnection()) {
    connections[connectionIndex]->retry();
  }
  connections[connectionIndex]->handle();
  isConnected = connections[connectionIndex]->isConnected;
  if (isConnected) {
    isConnecting = false;
  }

  if (connectionIndex < connections.size() - 1) {
    if (connections[connectionIndex]->connectionDidFail()) {
      Log("Connection did fail for index " + String(connectionIndex));
      connections[connectionIndex]->disconnect();
      connectionIndex = (connectionIndex + 1) % connections.size();
      connections[connectionIndex]->connect();
      return;
    }
  }

  if (isConnected && (connectionIndex == 0)) {
    return;
  }

  if (betterConnectionIndex != -1) {
    connections[betterConnectionIndex]->handle();
    if (connections[betterConnectionIndex]->connectionDidComplete()) {
      connections[connectionIndex]->disconnect();
      connectionIndex = betterConnectionIndex;
      betterConnectionIndex = -1;
    } else if (connections[betterConnectionIndex]->connectionDidFail()) {
      connections[betterConnectionIndex]->disconnect();
      betterConnectionIndex = -1;
    }
  }

  if (betterConnectionIndex == -1) {
    for(int b = 0; b < connectionIndex; b++) {
      if (connections[b]->wantsToRetryConnection()) {
        betterConnectionIndex = b;
        connections[b]->retry();
        Log("Retrying connection " + String(b));
        break;
      }
    }
  }

}

void OneOfMultipleConnection::retry() {
  Log("Retrying... " + String(connectionIndex));
  connectionIndex = 0;
  Connections::retry();
}
