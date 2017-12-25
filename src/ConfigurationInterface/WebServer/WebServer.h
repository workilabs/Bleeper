#pragma once

#include "ConfigurationInterface/ConfigurationInterface.h"
#include "Configuration/StringConvertibleVariable.h"
#include <vector>
#include <map>

#define HTTP_STATUS_OK 200
#define HTTP_STATUS_SERVER_ERROR 500
#define CONTENT_TYPE_HTML "text/html"
#define CONTENT_TYPE_JS "application/javascript"
#define CONTENT_TYPE_CSS "text/css"

class WebServer: public ConfigurationInterface {
protected:
  int port;
public:
  WebServer(int port);
  virtual void init() = 0;
  virtual void handle() = 0;
  virtual String buildPage(const std::vector<StringConvertibleVariable*> &);
  virtual const char* getJS();
  virtual const char* getStyle();
  virtual void saveValues(const std::map<String, String> &);
};
