#pragma once
#include "Arduino.h"
#include <map>

enum HTTPMethod {
  GET,
  POST,
  UNKNOWN,
};

class HTTPRequest {
private:
  bool readingData = false;
  bool firstLine = true;
  int dataLength = 0;
  String line;
  HTTPMethod method;
  String route;
  String data;
  std::map<String, String> args;
  bool _isFinished = false;
  bool hasData();
public:
  void add(const char c);
  bool isFinished();
  HTTPMethod getMethod();
  String getRoute();
  std::map<String, String> getArgs();
};
