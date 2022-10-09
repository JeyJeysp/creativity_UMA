int encendido;

void setup() {
  Serial.begin(9600);
  encendido = 0;
}

void loop() {
  if (!encendido){
    if (analogRead(A0) < 200){
      encendido = 1;
      digitalWrite(2, 1);
      delay(200);
    }
  } else {
    if (analogRead(A1) > 600){
      encendido = 0;
      digitalWrite(2, 0);
      delay(200);
    }
  }

  delay(100);
}
