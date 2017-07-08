#include "Bleeper/BleeperClass.h"
#include "Helpers/macros.h"

#define FunctionsContainer BleeperClass::ConnectionFunctions

FunctionsContainer& FunctionsContainer::set(Connection* c) {
  Bleeper.userProperties.connection = c;
  return *this;
}

FunctionsContainer& FunctionsContainer::setMultipleConnections(std::vector<Connection*> connections) {
  Bleeper.userProperties.connection = new MultipleConnection(connections);
  return *this;
}

FunctionsContainer& FunctionsContainer::setSingleConnectionFromPriorityList(std::vector<Connection*> connections) {
  Bleeper.userProperties.connection = new OneOfMultipleConnection(connections);
  return *this;
}
