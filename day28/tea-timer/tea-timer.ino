#include "Button.h"

enum TeaState { STATE_IDLE,
                STATE_BREWING,
                STATE_READY };
TeaState teaState = STATE_IDLE;

Button button = { 4, false, false, 0, 50 };

const int greenPin = 17;
const int yellowPin = 16;
const int redPin = 18;
const int buzzerPin = 19;
int ledPins[] = { greenPin, yellowPin, redPin };
int ledCount = sizeof(ledPins) / sizeof(ledPins[0]);

const unsigned long brewDuration = 30000;  // ms
const unsigned long readyTimeout = 10000;  // ms
const unsigned long blinkInterval = 500;   // ms
const unsigned long printInterval = 1000;  // ms
const unsigned long beepInterval = 400;    // ms

unsigned long brewStartTime = 0;
unsigned long readyStartTime = 0;
unsigned long lastLedBlink = 0;
unsigned long lastPrinted = 0;
unsigned long lastBeepToggle = 0;
bool ledBlinkOn = false;

void showLed(int onPin, bool isOn) {
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(ledPins[i], isOn && ledPins[i] == onPin);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(buzzerPin, OUTPUT);
  for (int i = 0; i < ledCount; i++) { pinMode(ledPins[i], OUTPUT); }
  setUpButton(&button);
  Serial.println("Mode: IDLE");
}

void loop() {
  unsigned long now = millis();
  bool pressed = buttonPressed(&button);

  switch (teaState) {
    case STATE_IDLE:
      showLed(greenPin, HIGH);
      if (pressed) {
        teaState = STATE_BREWING;
        brewStartTime = now;
        Serial.println("Mode: BREWING");
      }
      break;

    case STATE_BREWING:
      if (now - lastLedBlink >= blinkInterval) {
        lastLedBlink = now;
        ledBlinkOn = !ledBlinkOn;
      }
      showLed(yellowPin, ledBlinkOn);
      if (now - lastPrinted >= printInterval) {
        lastPrinted = now;
        Serial.print("Time remaining is: ");
        Serial.print((brewDuration - (now - brewStartTime)) / 1000);
        Serial.println("s");
      }
      if (pressed) {
        Serial.println("Cancelled");
        Serial.println("Mode: IDLE");
        teaState = STATE_IDLE;
      } else if (now - brewStartTime >= brewDuration) {
        Serial.println("Tea is ready!!");
        readyStartTime = now;
        teaState = STATE_READY;
      }
      break;

    case STATE_READY:
      showLed(redPin, HIGH);
      if (now - lastBeepToggle >= beepInterval) {
        lastBeepToggle = now;
        tone(buzzerPin, 2000, 200);
      }
      if (pressed) {
        teaState = STATE_IDLE;
        Serial.println("Mode: IDLE");
        noTone(buzzerPin);
      } else if (now - readyStartTime >= readyTimeout) {
        Serial.println("Mode: IDLE");
        teaState = STATE_IDLE;
        noTone(buzzerPin);
      }
      break;
  }
}
