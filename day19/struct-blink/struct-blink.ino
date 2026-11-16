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

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < ledCount; i++) {
    pinMode(leds[i].ledPins, OUTPUT);
  }
}

void loop() {
  unsigned long now = millis();
  for (int i = 0; i < ledCount; i++) {
    if (now - leds[i].lastToggle >= leds[i].interval) {
      leds[i].lastToggle = now;
      leds[i].isOn = !leds[i].isOn;
      digitalWrite(leds[i].ledPins, leds[i].isOn);
    }
  }
}
