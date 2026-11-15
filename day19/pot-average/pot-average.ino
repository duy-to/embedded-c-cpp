const int potPin = 34;
const unsigned long printInterval = 500;
unsigned long lastPrintTime = 0;

void containValues(unsigned long* container, int count) {
  for (int i = 0; i < count; i++) {
    *(container + i) = analogRead(potPin);
    delay(5);
  }
}

void average(unsigned long* container, int count) {
  unsigned long sum = 0;
  for (int i = 0; i < count; i++) {
    sum += container[i];
  }
  float average = (float)sum / count;
  Serial.println(average);
}

void setup() {
  Serial.begin(115200);
}

void loop() {
  unsigned long container[8];
  unsigned long now = millis();
  if (now - lastPrintTime >= printInterval) {
    lastPrintTime = now;
    containValues(container, 8);
    average(container, 8);
  }
}
