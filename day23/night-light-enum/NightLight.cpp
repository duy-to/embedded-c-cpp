#include "NightLight.h"

float applyGamma(float targetBrightness) {
  float pwmValue = (pow((targetBrightness / 255.00), 2.2)) * 255.00;
  return pwmValue;
}
void autoMode(NightLight* lightPtr, int rawValue) {
  if (rawValue > lightPtr->brightThreshold) {
    analogWrite(lightPtr->ledPin, 0);
    if (lightPtr->ledOn == true) { Serial.println("Led is OFF!"); }
    lightPtr->ledOn = false;
  } else if (rawValue < lightPtr->darkThreshold) {
    analogWrite(lightPtr->ledPin, applyGamma(lightPtr->savedBrightness));
    if (lightPtr->ledOn == false) { Serial.println("Led is ON!"); }
    lightPtr->ledOn = true;
  } else {
    if (lightPtr->ledOn) {
      analogWrite(lightPtr->ledPin, applyGamma(lightPtr->savedBrightness));
    } else {
      analogWrite(lightPtr->ledPin, 0);
    }
  }
}

void ledMode(bool pressed, int pwmValue, int targetBrightness, int rawValue, NightLight* lightPtr) {
  if (pressed) {
    lightPtr->mode = (Mode)((lightPtr->mode + 1) % 3);
    switch (lightPtr->mode) {
      case MODE_OFF: Serial.println("MODE: OFF"); break;
      case MODE_ON:
        Serial.println("MODE: ON");
        lightPtr->ledOn = true;
        break;
      case MODE_AUTO: Serial.println("MODE: AUTO"); break;
      default: Serial.println("Unknown mode"); break;
    }
  }

  switch (lightPtr->mode) {
    case MODE_ON:
      setLedBrightness(pwmValue, lightPtr);
      lightPtr->savedBrightness = targetBrightness;
      break;
    case MODE_AUTO:
      autoMode(lightPtr, rawValue);
      break;
    case MODE_OFF:
    default:
      analogWrite(lightPtr->ledPin, 0);
      break;
  }
}

void setLedBrightness(float pwmValue, NightLight* lightPtr) {
  analogWrite(lightPtr->ledPin, pwmValue);
}
