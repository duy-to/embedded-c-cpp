#include "Button.h"

enum LedMode { MODE_OFF,
               MODE_ON,
               MODE_BLINK };
LedMode ledMode = MODE_OFF;

Button button = { 4, false, false, 0, 50 };
const int redPin = 18;

unsigned long blinkInterval = 500;  // ms, changed by "speed N"
unsigned long modeStartTime = 0;    // when the current mode began (for status)
unsigned long lastBlinkToggle = 0;  // last time the LED flipped in BLINK
bool ledOn = false;

const char* modeName(LedMode mode) {
  switch (mode) {
    case MODE_OFF: return "OFF";
    case MODE_ON: return "ON";
    case MODE_BLINK: return "BLINK";
  }
  return "?";
}

void setMode(LedMode newMode, unsigned long now) {
  ledMode = newMode;
  modeStartTime = now;
  Serial.print("Mode: ");
  Serial.println(modeName(ledMode));
}

String readCommand() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    command.toLowerCase();
    return command;
  }
  return "";
}

void setup() {
  Serial.begin(115200);
  pinMode(redPin, OUTPUT);
  setUpButton(&button);
  setMode(MODE_OFF, millis());
}

void loop() {
  unsigned long now = millis();
  bool pressed = buttonPressed(&button);
  String command = readCommand();
  float elapsed = (now - modeStartTime) / 1000.0;

  if (command.length() > 0) {
    if (command == "on") {
      setMode(MODE_ON, now);
    } else if (command == "off") {
      setMode(MODE_OFF, now);
    } else if (command == "blink") {
      setMode(MODE_BLINK, now);
    } else if (command.startsWith("speed ")) {
      int newInterval = command.substring(6).toInt();
      if (newInterval > 2000 || newInterval < 50) {
        Serial.println("Error: interval must be 50-2000 ms");
      } else {
        blinkInterval = newInterval;
        Serial.print("Interval: ");
        Serial.print(blinkInterval);
        Serial.println(" ms");
      }
    } else if (command == "status") {
      Serial.print("Mode: ");
      Serial.print(modeName(ledMode));
      Serial.print(", Interval: ");
      Serial.print(blinkInterval);
      Serial.print(" ms");
      Serial.print(", for ");
      Serial.print(elapsed, 1);
      Serial.println(" s");
    } else {
      Serial.print("Unknown command: ");
      Serial.println(command);
    }
  }

  switch (ledMode) {
    case MODE_OFF:
      ledOn = false;
      if (pressed) {
        setMode(MODE_ON, now);
      }
      break;
    case MODE_ON:
      ledOn = true;
      if (pressed) {
        setMode(MODE_BLINK, now);
      }
      break;
    case MODE_BLINK:
      if (now - lastBlinkToggle >= blinkInterval) {
        lastBlinkToggle = now;
        ledOn = !ledOn;
      }
      if (pressed) {
        setMode(MODE_OFF, now);
      }
      break;
  }
  digitalWrite(redPin, ledOn);
}
