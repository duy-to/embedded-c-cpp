const int pirPin = 27;
const int redPin = 18;

bool isMotion = false;
bool wasMotion = false;
unsigned long motionStartTime = 0;

void setup() {
  Serial.begin(115200);
  pinMode(pirPin, INPUT);
  pinMode(redPin, OUTPUT);
  Serial.println("PIR warming up...");
  delay(30000);
  Serial.println("PIR ready");
}

void loop() {
  isMotion = digitalRead(pirPin);

  if (isMotion != wasMotion) {
    if (isMotion) {
      motionStartTime = millis();
      digitalWrite(redPin, HIGH);
      Serial.print("Motion START at: ");
      Serial.print(motionStartTime / 1000.0, 1);
      Serial.println(" s");
    }
    else {
      unsigned long motionDuration = millis() - motionStartTime;
      Serial.print("Motion END, lasted ");
      digitalWrite(redPin, LOW);
      Serial.print(motionDuration / 1000.0, 1);
      Serial.println(" s");
    }
  }

  wasMotion = isMotion;
}
