#pragma once

#include "Bleeper/Initable.h"

class ConfigurationInterface: public Initable {
public:
  virtual void init() = 0;
  virtual void handle() = 0;
};
