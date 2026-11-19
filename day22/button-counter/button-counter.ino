#include "Button.h"
Button button = { 4, true, true, 0, 50 };
int Pressed = 0;
void setup() {
  Serial.begin(115200);
  setUpButton(&button);
}

void loop() {
  if (buttonPressed(&button)) {
    Pressed++;
    Serial.print("Pressed ");
    Serial.print(Pressed);
    Serial.println(" Times");
  }
}
