#pragma once

#include "Bleeper/Initable.h"

class Storage: public Initable {
public:
  virtual void persist() = 0;
  virtual void load() = 0;
};
