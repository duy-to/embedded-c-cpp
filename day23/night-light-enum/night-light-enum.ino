// Night light with 3 modes and gamma-corrected brightness (ESP32)
//
// Modes (button cycles OFF -> ON -> AUTO -> OFF ...):
//   OFF  : LED off
//   ON   : pot sets brightness (0-255, gamma 2.2); last value is saved
//   AUTO : pot acts as a light sensor (low = dark)
//          dark   (pot < 1200) -> LED on at saved brightness
//          bright (pot > 1500) -> LED off
//          1200-1500           -> keep current state (hysteresis, no flicker)
//
// Button:
//   Debounce 50 ms with millis(), count on the press edge only
//   Prints the new mode name once per press
//
// Brightness:
//   target = pot >> 4            (0-4095 -> 0-255)
//   pwm    = (target / 255)^2.2 * 255
//
// Pins:
//   LED    : GPIO18 (220 ohm)
//   Button : GPIO4 -> GND, internal pull-up (INPUT_PULLUP, pressed = LOW)
//   Pot    : wiper -> GPIO34 (ADC 0-4095)
//            later replaced by LDR + 10k divider on the same pin
//
// Serial (115200): pot, target and pwm every 200 ms;
//   "Led is ON!" / "Led is OFF!" only when AUTO changes state
#include "NightLight.h"
#include "Button.h"

const int potPin = 34;
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
  int rawValue = analogRead(potPin);
  int targetBrightness = rawValue >> 4;
  int pwmValue = applyGamma(targetBrightness);
  ledMode(buttonPressed(&modeButton), pwmValue, targetBrightness, rawValue, &light);
  if (now - lastPrinted >= printInterval) {
    Serial.print("Potentiometer Value: ");
    Serial.println(rawValue);
    Serial.print("Target brightness: ");
    Serial.println(targetBrightness);
    Serial.print("PWM value: ");
    Serial.println(pwmValue);
    lastPrinted = now;
  }
}
