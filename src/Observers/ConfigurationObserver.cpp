#include "Observers/ConfigurationObserver.h"

bool ConfigurationObserver::isEnabled = true;

ConfigurationObserver::ConfigurationObserver() {}

void ConfigurationObserver::setFilter(std::set<VariableAddress> addressFilter) {
  this->addressFilter = addressFilter;
}

bool ConfigurationObserver::isInterestedIn(VariableAddress address) {
  return ConfigurationObserver::isEnabled && (addressFilter.empty() || (addressFilter.find(address) != addressFilter.end()));
}
