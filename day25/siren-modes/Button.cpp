#include "Button.h"

void setUpButton(Button* buttonPtr) {
  pinMode(buttonPtr->buttonPin, INPUT_PULLUP);
}

bool buttonPressed(Button* buttonPtr) {
  unsigned long now = millis();
  bool reading = digitalRead(buttonPtr->buttonPin);
  bool pressed = false;
  if (reading != buttonPtr->lastReading) {
    buttonPtr->lastChangeTime = now;
    buttonPtr->lastReading = reading;
  }
  if (now - buttonPtr->lastChangeTime >= buttonPtr->debounceInterval) {
    if (reading == 0 && buttonPtr->stableReading == 1) {
      pressed = true;
    }
    buttonPtr->stableReading = reading;
  }
  return pressed;
}