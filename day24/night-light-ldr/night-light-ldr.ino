// Night light with 3 modes and an LDR light sensor (ESP32)
//
// Modes (button cycles OFF -> ON -> AUTO -> OFF ...):
//   OFF  : LED off
//   ON   : LED on at fixed brightness (savedBrightness, gamma 2.2)
//   AUTO : LDR reads room light (low = dark)
//          dark   (ldr < darkThreshold)   -> LED on at saved brightness
//          bright (ldr > brightThreshold) -> LED off
//          in between                     -> keep current state (hysteresis, no flicker)
//          thresholds from Serial: room 4095, partly covered 2430, covered 800
//
// Button:
//   Debounce 50 ms with millis(), count on the press edge only
//   Prints the new mode name once per press
//
// Brightness:
//   pwm = (savedBrightness / 255)^2.2 * 255
//
// Pins:
//   LED    : GPIO18 (220 ohm)
//   Button : GPIO4 -> GND, internal pull-up (INPUT_PULLUP, pressed = LOW)
//   LDR    : 3V3 -> LDR -> GPIO34 -> 10k -> GND (more light = higher reading)
//
// Serial (115200): LDR value every 200 ms;
//   "Led is ON!" / "Led is OFF!" only when AUTO changes state
#include "NightLight.h"
#include "Button.h"

const int ldrPin = 34;
// Measured: room light 4095, partly covered 2430, fully covered 800
// darkThreshold 1200, brightThreshold 1500
NightLight light = { 18, MODE_OFF, 128, false, 1200, 1500 };

unsigned long lastPrinted = 0;
unsigned long printInterval = 200;

Button modeButton = { 4, true, true, 0, 50 };

void setup() {
  Serial.begin(115200);
  setUpButton(&modeButton);
}

void loop() {
  unsigned long now = millis();
  int ldrValue = analogRead(ldrPin);
  ledMode(buttonPressed(&modeButton), ldrValue, &light);
  if (now - lastPrinted >= printInterval) {
    Serial.print("LDR value: ");
    Serial.println(ldrValue);
    lastPrinted = now;
  }
}
