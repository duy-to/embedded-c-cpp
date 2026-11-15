void clampValue(int* x, int low, int high) {
  if (*x >= high) {
    *x = high;
  } else if (*x <= low) {
    *x = low;
  }
}

void setup() {
  Serial.begin(115200);
  int number1 = -5;
  int number2 = 50;
  int number3 = 300;
  clampValue(&number1, 0, 255);
  Serial.println(number1);
  clampValue(&number2, 0, 255);
  Serial.println(number2);
  clampValue(&number3, 0, 255);
  Serial.println(number3);
}

void loop() {
}
