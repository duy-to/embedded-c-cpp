#pragma once
#include <Arduino.h>

struct Button {
  int buttonPin;
  bool lastReading;
  bool stableReading;
  unsigned long lastChangeTime;
  unsigned long debounceInterval;
};

void setUpButton(Button* buttonPtr);
bool buttonPressed(Button* buttonPtr);
