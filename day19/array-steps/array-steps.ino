int array[3] = { 1, 2, 3 };
byte array1[3] = { 0b0001, 0b0010, 0b0011 };

void function(int* p) {
  Serial.println(sizeof(p));
}

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 3; i++) {
    Serial.println((uint32_t)(array + i), HEX);
  }
  Serial.println(array[1]);
  Serial.println(*(array + 1));

  for (int i = 0; i < 3; i++) {
    Serial.println((uint32_t)(array1 + i), HEX);
  }
  Serial.println(array1[1], BIN);
  Serial.println(*(array1 + 1));
  Serial.println(sizeof(array));
  function(array);
}

void loop() {
}
