#include "ConfigurationInterface/WebServer/ESP32/HTTPRequest.h"
#include "Helpers/Logger.h"
#include "Helpers/utils.h"

void HTTPRequest::add(const char c) {
  if (readingData) {
    if ((c == '\n') || (c == '\r')) return;
    data += c;
    dataLength--;
    if (!dataLength) {
      auto pairs = splitString(data, '&');
      for(auto p: pairs) {
        auto split = splitString(p, '=');
        if (split.size() == 2) {
          args[split[0]] = split[1];
        }
      }
      _isFinished = true;
      return;
    }
    return;
  }

  if (c == '\n') {
    if ((line.length() == 0) && (!hasData())) {
      _isFinished = true;
    } else if (hasData()) {
      readingData = true;
    } else {
      if (firstLine) {
        if (line.startsWith("GET")) {
          method = GET;
        } else if (line.startsWith("POST")) {
          method = POST;
        } else {
          method = UNKNOWN;
        }
        firstLine = false;
        auto strings = splitString(line, ' ');
        if (strings.size() > 1)
          route = strings[1];
      }
      if (line.startsWith("Content-Length:")) {
        dataLength = line.substring(15).toInt();
      }
      line = "";
    }
  } else if (c != '\r') {
    line += c;
  }
}

bool HTTPRequest::hasData() {
  return (dataLength > 0);
}

bool HTTPRequest::isFinished() {
  return _isFinished;
}

HTTPMethod HTTPRequest::getMethod() {
  return method;
}

String HTTPRequest::getRoute() {
  return route;
}

std::map<String, String> HTTPRequest::getArgs() {
  return args;
}
