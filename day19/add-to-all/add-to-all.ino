void addToAll(int* array, int count, int add) {
  for (int i = 0; i < count; i++) {
    *(array + i) += add;
  }
}

void setup() {
  Serial.begin(115200);
  int array[3] = { 0, 10, 20 };
  addToAll(array, 3, 10);
  for (int i = 0; i < 3; i++) {
    Serial.println(array[i]);
  }
}

void loop() {
}
