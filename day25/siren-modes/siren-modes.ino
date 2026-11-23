#include "Button.h"
Button button = { 4, false, false, 0, 50 };
enum Mode { MODE_OFF,
            MODE_BEEP,
            MODE_SIREN };
Mode mode = MODE_OFF;

const int greenPin = 17;
const int yellowPin = 16;
const int redPin = 18;

int ledPins[] = { greenPin, yellowPin, redPin };
int ledCount = sizeof(ledPins) / sizeof(ledPins[0]);
const int buzzerPin = 19;
bool switchSound = false;

bool ledBlinkOn = true;
unsigned long lastLedBlink = 0;
const unsigned long ledBlinkInterval = 250;


void showModeLed(int onPin) {
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(ledPins[i], ledBlinkOn && ledPins[i] == onPin);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(buzzerPin, OUTPUT);
  setUpButton(&button);
  Serial.println("MODE_OFF");
  for (int i = 0; i < ledCount; i++) { pinMode(ledPins[i], OUTPUT); }
}
unsigned long lastSiren = 0;
unsigned long lastBeep = 0;
unsigned long beepInterval = 400;
unsigned long sirenInterval = 300;
void loop() {
  bool pressed = buttonPressed(&button);
  if (millis() - lastLedBlink >= ledBlinkInterval) {
    lastLedBlink = millis();
    ledBlinkOn = !ledBlinkOn;
  }
  switch (mode) {
    case MODE_OFF:
      showModeLed(greenPin);
      noTone(buzzerPin);
      if (pressed) {
        Serial.println("MODE_BEEP");
        mode = MODE_BEEP;
      }
      break;
    case MODE_BEEP:
      showModeLed(yellowPin);
      if (millis() - lastBeep >= beepInterval) {
        lastBeep = millis();
        tone(buzzerPin, 2000, 200);
      }
      if (pressed) {
        Serial.println("MODE_SIREN");
        mode = MODE_SIREN;
      }
      break;
    case MODE_SIREN:
      showModeLed(redPin);
      if (millis() - lastSiren >= sirenInterval) {
        if (switchSound) {
          lastSiren = millis();
          tone(buzzerPin, 1500, 300);
          switchSound = !switchSound;
        } else {
          lastSiren = millis();
          tone(buzzerPin, 2200, 300);
          switchSound = !switchSound;
        }
      }
      if (pressed) {
        Serial.println("MODE_OFF");
        mode = MODE_OFF;
      }
      break;
  }
}
