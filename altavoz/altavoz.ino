//--------------------------------------------------//
// PRUEBA_1: Altavoz                                //
// AUTORES: A Pena Castillo, JJ Navarrete Galvez    //
//--------------------------------------------------//


// --- Definiciones --- //
//#define intervalo 150
#define un_segundo 1000
#define PIN_SP 13


// --- Variables globales --- //
unsigned long tiempo = 0;
bool estadoLED = 0;
//int sonido[] = {500, 450, 400, 350, 225};
int sonido2 = 500;
int i = 0;


// --- Setup y Loop --- //
void setup() {
  Serial.begin(9600);
  pinMode(PIN_SP, OUTPUT);
}

void loop() {
  tone(PIN_SP, sonido2);
  delay(50);

  if (sonido2 != 100)
    sonido2 -= 10;
  else{
    delay(150);

    noTone(PIN_SP);
    delay(1000);
  }


  
  
  /*tone(PIN_SP, sonido[i]);
  delay(150);

  if (i != 4)
    i++;
  else{
    delay(350);

    noTone(PIN_SP);
    delay(500);
  }*/
  
  
  
  /*//generar tono de 440Hz durante 1000 ms
  tone(PIN_SP, 650);
  delay(250);

  tone(PIN_SP, 150);
  delay(1000);
  
  //detener tono durante 500ms  
  noTone(PIN_SP);
  delay(500);
  
  //generar tono de 523Hz durante 500ms, y detenerlo durante 500ms.
  tone(PIN_SP, 523, 300);
  delay(500);*/
  
  
  /*unsigned long tiempo_act = millis();  

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
  }*/
}
