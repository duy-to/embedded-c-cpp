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

NightLight light = { 18, MODE_OFF, 128, false, 1200, 1500 };

const int buttonPin = 4;
const int potPin = 34;

bool lastReading = 0;
bool stableReading = 1;
unsigned long lastChangeTime = 0;
unsigned long debounceInterval = 50;

unsigned long lastPrinted = 0;
unsigned long printInterval = 200;

bool buttonPressed() {
  unsigned long now = millis();
  bool reading = digitalRead(buttonPin);
  bool pressed = false;
  if (reading != lastReading) {
    lastChangeTime = now;
    lastReading = reading;
  }
  if (now - lastChangeTime >= debounceInterval) {
    if (reading == 0 && stableReading == 1) {
      pressed = true;
    }
    stableReading = reading;
  }
  return pressed;
}

void ledMode(bool pressed, int pwmValue, int targetBrightness, int rawValue) {
  if (pressed) {
    light.mode = (light.mode + 1) % 3;
    if (light.mode == MODE_OFF) {
      Serial.println("MODE: OFF");
    } else if (light.mode == MODE_ON) {
      Serial.println("MODE: ON");
      light.ledOn = true;
    } else if (light.mode == MODE_AUTO) {
      Serial.println("MODE: AUTO");
    }
  }
  if (light.mode == MODE_OFF) {
    analogWrite(light.ledPin, 0);
  } else if (light.mode == MODE_ON) {
    setLedBrightness(pwmValue);
    light.savedBrightness = targetBrightness;
  } else if (light.mode == MODE_AUTO) {
    autoMode(&light, rawValue);
  }
}

float applyGamma(float targetBrightness) {
  float pwmValue = (pow((targetBrightness / 255.00), 2.2)) * 255.00;
  return pwmValue;
}

void setLedBrightness(float pwmValue) {
  analogWrite(light.ledPin, pwmValue);
}

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP);
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

void loop() {
  unsigned long now = millis();
  int rawValue = analogRead(potPin);
  int targetBrightness = rawValue >> 4;
  int pwmValue = applyGamma(targetBrightness);
  ledMode(buttonPressed(), pwmValue, targetBrightness, rawValue);
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
