struct Led {
  int ledPins;
  unsigned long lastToggle;
  bool isOn;
  int interval;
};

Led leds[3] = { { 18, 0, false, 500 },
                { 17, 0, false, 300 },
                { 16, 0, false, 1000 } };
const int ledCount = sizeof(leds) / sizeof(leds[0]);

void updateLed(Led* b, unsigned long now) {
  if (now - (b->lastToggle) >= (b->interval)) {
    b->lastToggle = now;
    b->isOn = !b->isOn;
    digitalWrite(b->ledPins, b->isOn);
  }
}

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < ledCount; i++) {
    pinMode(leds[i].ledPins, OUTPUT);
  }
}

void loop() {
  unsigned long now = millis();
  for (int i = 0; i < ledCount; i++) {
    updateLed(&leds[i], now);
  }
}
