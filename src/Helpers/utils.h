#include <vector>
#include "Arduino.h"

void configureLed(int led);
void flashLed(int led, int onMs, int offMs, int times);
std::vector<String> splitString(String string, char delimiter);
