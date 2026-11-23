// Room alarm with PIR motion sensor (ESP32)
//
// States:
//   DISARMED : green LED on, silent, PIR ignored. Button -> ARMING
//   ARMING   : 10 s exit delay. Yellow LED blinks 250 ms, 2000 Hz chirp (50 ms) every 1 s
//              Button -> DISARMED (cancel), after 10 s -> ARMED
//   ARMED    : yellow LED on, silent. Motion -> ALARM, button -> DISARMED
//   ALARM    : red LED blinks 100 ms, siren 1500 / 2200 Hz switching every 300 ms
//              Keeps sounding after motion stops. Button -> DISARMED (silent at once)
//
// Pins:
//   PIR     : HC-SR501 OUT -> GPIO27 (VCC -> VIN 5V), 30 s warm-up at power-on
//   Button  : GPIO4 (Button.h, 50 ms debounce)
//   LEDs    : GREEN 17, YELLOW 16, RED 18 (220 ohm each)
//   Buzzer  : passive buzzer on 5V, switched by IRLZ44N, gate <- GPIO19 (100 ohm, 10k pull-down)
//
// Serial (115200): one line per state change, e.g. "State: ARMED", "MOTION! State: ALARM"

#include "Button.h"

enum AlarmState { STATE_DISARMED,
                  STATE_ARMING,
                  STATE_ARMED,
                  STATE_ALARM };
AlarmState alarmState = STATE_DISARMED;

Button button = { 4, false, false, 0, 50 };

const int pirPin = 27;
const int greenPin = 17;
const int yellowPin = 16;
const int redPin = 18;
const int buzzerPin = 19;
int ledPins[] = { greenPin, yellowPin, redPin };
int ledCount = sizeof(ledPins) / sizeof(ledPins[0]);

const unsigned long armingDelay = 10000;
unsigned long armingStartTime = 0;

bool ledBlinkOn = false;
unsigned long lastLedBlink = 0;
unsigned long yellowLedBlinkInterval = 250;
unsigned long redLedBlinkInterval = 100;
unsigned long lastChirp = 0;
unsigned long chirpInterval = 1000;
unsigned long lastSirenSwitch = 0;  // ALARM siren timer
unsigned long sirenInterval = 300;
bool isHighTone = false;

void showLed(int onPin, bool isOn) {
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(ledPins[i], isOn && ledPins[i] == onPin);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(pirPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  for (int i = 0; i < ledCount; i++) { pinMode(ledPins[i], OUTPUT); }
  setUpButton(&button);
  Serial.println("PIR warming up...");
  delay(30000);
  Serial.println("PIR ready");
  Serial.println("State: DISARMED");
}

void loop() {
  unsigned long now = millis();
  bool pressed = buttonPressed(&button);
  bool isMotion = digitalRead(pirPin) == HIGH;

  switch (alarmState) {
    case STATE_DISARMED:
      showLed(greenPin, HIGH);
      noTone(buzzerPin);
      if (pressed) {
        armingStartTime = millis();
        Serial.println("State: ARMING");
        alarmState = STATE_ARMING;
      }
      break;

    case STATE_ARMING:
      if (millis() - lastLedBlink >= yellowLedBlinkInterval) {
        lastLedBlink = millis();
        ledBlinkOn = !ledBlinkOn;
      }
      showLed(yellowPin, ledBlinkOn);
      if (millis() - lastChirp >= chirpInterval) {
        lastChirp = millis();
        tone(buzzerPin, 2000, 50);
      }
      if (pressed) {
        Serial.println("State: DISARMED");
        alarmState = STATE_DISARMED;
      }
      else if (millis() - armingStartTime >= armingDelay) {
        alarmState = STATE_ARMED;
        Serial.println("State: ARMED");
      }
      break;

    case STATE_ARMED:
      showLed(yellowPin, HIGH);
      noTone(buzzerPin);
      if (pressed) {
        Serial.println("State: DISARMED");
        alarmState = STATE_DISARMED;
      } else if (isMotion) {
        Serial.println("MOTION! State: ALARM");
        alarmState = STATE_ALARM;
      }
      break;

    case STATE_ALARM:
      if (millis() - lastLedBlink >= redLedBlinkInterval) {
        lastLedBlink = millis();
        ledBlinkOn = !ledBlinkOn;
      }
      showLed(redPin, ledBlinkOn);
      if (millis() - lastSirenSwitch >= sirenInterval) {
        if (isHighTone) {
          lastSirenSwitch = millis();
          tone(buzzerPin, 1500, 300);
          isHighTone = !isHighTone;
        } else {
          lastSirenSwitch = millis();
          tone(buzzerPin, 2200, 300);
          isHighTone = !isHighTone;
        }
      }
      if (pressed) {
        Serial.println("State: DISARMED");
        alarmState = STATE_DISARMED;
      }
      break;
  }
}
