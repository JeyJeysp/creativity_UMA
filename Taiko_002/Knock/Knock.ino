//--------------------------------------------------//
// EJERCICIO 2: XXX-Hero                            //
// AUTORES: A Pena Castillo, JJ Navarrete Galvez    //
//--------------------------------------------------//


// --- Definiciones --- //
#define intervalo 150
#define un_segundo 1000
#define UMBRAL 250
#define DISCO_1 A0
//#define PIN_LED 13      //Para pruebas


// --- Variables globales --- //
unsigned long tiempo = 0;
int continuar = 1;
//int estadoLED = LOW;     //Para pruebas


// --- Setup y Loop --- //
void setup() {
  Serial.begin(9600);
  //pinMode(PIN_LED,OUTPUT);
}

void loop() {
  int lectura = 0;
  
  if (continuar == 1){
    lectura = analogRead(DISCO_1);
    //Serial.println(lectura);
    
    if(lectura >= UMBRAL){
      //estadoLED != estadoLED;
      //digitalWrite(PIN_LED, estadoLED);
      
      Serial.println("Knock!");

      tiempo = millis() + intervalo;
      continuar = 0;
    }
  } else {
    unsigned long tiempo2 = millis();
    if (tiempo2 > tiempo){
      tiempo = 0;
      continuar = 1;
    }
  } 
}
