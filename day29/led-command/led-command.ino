bool state = false;
const int redPin = 18;

void setup() {
  Serial.begin(115200);
  pinMode(redPin, OUTPUT);
  Serial.println("Ready. Commands: on, off, toggle, status");
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    command.toLowerCase();

    if (command.length() == 0) {
      return;
    }

    if (command == "on") {
      state = true;
      digitalWrite(redPin, state);
      Serial.println("LED ON");
    } else if (command == "off") {
      state = false;
      digitalWrite(redPin, state);
      Serial.println("LED OFF");
    } else if (command == "toggle") {
      state = !state;
      digitalWrite(redPin, state);
      if (state) {
        Serial.println("LED ON");
      } else {
        Serial.println("LED OFF");
      }
    } else if (command == "status") {
      if (state) {
        Serial.println("LED is ON");
      } else {
        Serial.println("LED is OFF");
      }
    } else {
      Serial.print("Unknown command: ");
      Serial.println(command);
    }
  }
}
