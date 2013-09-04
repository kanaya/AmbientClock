void setup() {
  pinMode(2, INPUT);
  digitalWrite(2, HIGH);
  pinMode(4, INPUT);
  digitalWrite(4, HIGH);
  pinMode(5, INPUT);
  digitalWrite(5, HIGH);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}

void loop() {
  int p2;
  p2 = digitalRead(2);
  digitalWrite(13, p2);
  delay(100);
}

