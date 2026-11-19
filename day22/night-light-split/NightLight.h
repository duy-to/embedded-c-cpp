#pragma once
#include <Arduino.h>

const int MODE_OFF = 0;
const int MODE_ON = 1;
const int MODE_AUTO = 2;

struct NightLight {
  int ledPin;
  int mode;
  int savedBrightness;
  bool ledOn;
  int darkThreshold;
  int brightThreshold;
};

float applyGamma(float targetBrightness);
void autoMode(NightLight* lightPtr, int rawValue);
void ledMode(bool pressed, int pwmValue, int targetBrightness, int rawValue, NightLight* lightPtr);
void setLedBrightness(float pwmValue, NightLight* lightPtr);
