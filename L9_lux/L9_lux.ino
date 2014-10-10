void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(A0);
  int lux = 2.09 * sensorValue - 856.05;
  Serial.println(lux);
  delay(100);
}
