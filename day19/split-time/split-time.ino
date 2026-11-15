void splitTime(int time, int* minutes, int* seconds) {
  *minutes = (time / 1000) / 60;
  *seconds = (time / 1000) % 60;
}

void setup() {
  Serial.begin(115200);
  int time = 100000;
  int m;
  int s;
  splitTime(time, &m, &s);
  Serial.println(m);
  Serial.println(s);
}

void loop() {
}
