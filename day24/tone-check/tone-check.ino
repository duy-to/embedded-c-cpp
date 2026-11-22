const int buzzerPin = 18;
void setup() {
  Serial.begin(115200);
  pinMode(buzzerPin, OUTPUT);
  tone(buzzerPin, 440);
  delay(2000);
  Serial.println("after tone");
  noTone(buzzerPin);
}

void loop() {}
