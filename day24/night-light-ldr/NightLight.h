#pragma once
#include <Arduino.h>

enum Mode { MODE_OFF,
            MODE_ON,
            MODE_AUTO };

struct NightLight {
  int ledPin;
  Mode mode;
  int savedBrightness;
  bool ledOn;
  int darkThreshold;
  int brightThreshold;
};

float applyGamma(float targetBrightness);
void autoMode(NightLight* lightPtr, int ldrValue);
void ledMode(bool pressed, int ldrValue, NightLight* lightPtr);
void setLedBrightness(float pwmValue, NightLight* lightPtr);
