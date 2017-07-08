#include "utils.h"

std::vector<String> splitString(String string, char delimiter){
  std::vector<String> result;
  int lastStart = 0;
  for(int i = 0; i < string.length(); i++){
    if (string.charAt(i) == delimiter){
      result.push_back(string.substring(lastStart,i));
      lastStart = i+1;
    }
  }
  if (lastStart < string.length()){
    result.push_back(string.substring(lastStart,string.length()));
  }
  return result;
}

void flashLed(int led, int onMs, int offMs, int times){
  for(int i = 0; i < times; i++){
    digitalWrite(led,LOW);
    delay(onMs);
    digitalWrite(led,HIGH);
    delay(offMs);
  }
}

void configureLed(int led) {
  pinMode(led,OUTPUT);
  digitalWrite(led,HIGH);
  flashLed(led, 300,250,3);
}
