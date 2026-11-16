const int pwmPin = 19;
const int readPin = 35;
const int sampleCount = 200;

void setup() {
  Serial.begin(115200);
  pinMode(readPin, INPUT);
  analogWrite(pwmPin, 128);
}

void loop() {
  int maxMv = 0;
  int minMv = 5000;

  for (int i = 0; i < sampleCount; i++) {
    int reading = analogReadMilliVolts(readPin);
    if (reading > maxMv) {
      maxMv = reading;
    }
    if (reading < minMv) {
      minMv = reading;
    }
  }

  Serial.print("min: ");
  Serial.print(minMv);
  Serial.print(" mV  max: ");
  Serial.print(maxMv);
  Serial.print(" mV  ripple: ");
  Serial.print(maxMv - minMv);
  Serial.println(" mV");
  delay(500);
}
