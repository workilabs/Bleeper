#pragma once
#include "Connection.h"

class AP: public Connection {
public:
    virtual void connect();
    virtual void disconnect();
    virtual void init();
    virtual void handle();
};
