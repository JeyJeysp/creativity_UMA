//--------------------------------------------------//
// EJERCICIO 3: Laser Tag!                          //
// AUTORES: A Pena Castillo, JJ Navarrete Galvez    //
//--------------------------------------------------//


// --- Definiciones --- //
//#define intervalo 150
#define un_segundo 1000
#define UMBRAL 475
#define LDR A0
#define PIN_LED 13
#define on 1
#define off 0


// --- Variables globales --- //
unsigned long tiempo = 0;
bool estadoLED = 0;


// --- Setup y Loop --- //
void setup() {
  Serial.begin(9600);
  pinMode(PIN_LED, OUTPUT);
}

void loop() {
  unsigned long tiempo_act = millis();  

  if (!tiempo){
    int lectura = analogRead(LDR);

    if (lectura < UMBRAL){
      //Serial.println("tocado!!!");

      tiempo = tiempo_act;
      estadoLED != estadoLED;
      Serial.println(estadoLED);
      digitalWrite(PIN_LED, 1);
    }
  } else if (tiempo_act > tiempo + un_segundo){
    tiempo = 0;
    
    estadoLED != estadoLED;
          Serial.println(estadoLED);
    digitalWrite(PIN_LED, 0);
  }
}
