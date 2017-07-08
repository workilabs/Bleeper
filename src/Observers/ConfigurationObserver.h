#pragma once
#include "Configuration/ConfigMap.h"
#include <set>

struct ConfigurationPropertyChange {
  String key;
  String oldValue;
  String newValue;
};

class ConfigurationObserver {
protected:
  std::set<VariableAddress> addressFilter;
public:
  static bool isEnabled;
  ConfigurationObserver();
  void setFilter(std::set<VariableAddress> addressFilter);
  virtual bool isInterestedIn(VariableAddress address);
  virtual void onConfigurationChanged(const ConfigurationPropertyChange value) = 0;
};
