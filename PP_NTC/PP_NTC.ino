void setup() {
  Serial.begin(9600);
}

void loop() {
  //double lectura = analogRead(A0);
  //Serial.print("NTC en A0: ");
  Serial.println(analogRead(A0));
  //Serial.print("Micro en A1: ");
  //Serial.println(analogRead(A1));
  //Serial.println();

  delay(10);
}
