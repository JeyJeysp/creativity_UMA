int encendido;

void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  encendido = 0;
}

void loop() {
  if (!encendido){
    int valor = analogRead(A0);
    Serial.print("NTC: ");
    Serial.println(valor);
    if (valor < 350){
      encendido = 1;
      digitalWrite(2, 1);
      delay(1000);
    }
  } else {
    int valor2 = analogRead(A1);
    Serial.print("Micro: ");
    Serial.println(valor2);
    if (valor2 > 550){
      encendido = 0;
      digitalWrite(2, 0);
      delay(1000);
    }
  }

  delay(50);
}
