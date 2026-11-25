struct Led {
  int pin;
  bool isOn;
  unsigned long lastToggle;
  unsigned long interval;
};

Led leds[] = { { 17, false, 0, 200 },
               { 16, false, 0, 500 },
               { 18, false, 0, 1000 } };

int ledCount = sizeof(leds) / sizeof(leds[0]);
void setup() {
  Serial.begin(115200);
  for (int i = 0; i < ledCount; i++) {
    pinMode(leds[i].pin, OUTPUT);
  }
}

void showLed(Led* ledPtr, unsigned long now) {
  if (now - (ledPtr->lastToggle) >= (ledPtr->interval)) {
    ledPtr->isOn = !ledPtr->isOn;
    ledPtr->lastToggle = now;
    digitalWrite(ledPtr->pin, ledPtr->isOn);
    Serial.print("LED: ");
    Serial.print(ledPtr->pin);
    Serial.print(" is ");
    if (ledPtr->isOn) {
      Serial.println("ON");
    } else {
      Serial.println("OFF");
    }
  }
}
void loop() {
  unsigned long now = millis();
  for (int i = 0; i < ledCount; i++) {
    showLed(&leds[i], now);
  }
}
