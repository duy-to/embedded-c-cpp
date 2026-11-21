const int buzzerPin = 18;
int freq[] = { 2, 10, 50, 500 };
void playSquareWave(int pin, float frequency, unsigned long durationMs) {

  float halfPeriod = 1000000UL / (2 * frequency);
  unsigned long startTime = millis();
  while (millis() - startTime < durationMs) {
    digitalWrite(pin, HIGH);
    delayMicroseconds(halfPeriod);
    digitalWrite(pin, LOW);
    delayMicroseconds(halfPeriod);
  }
}
void setup() {
  Serial.begin(115200);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  for (int i = 0; i < sizeof(freq) / sizeof(freq[0]); i++) {
    Serial.println(freq[i]);
    playSquareWave(buzzerPin, freq[i], 3000);
  }
}
