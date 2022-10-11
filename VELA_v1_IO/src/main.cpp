#include <Arduino.h>

int encendido, valor_ant;


void setup() {
  Serial.begin(9600);
  encendido = 0;
  valor_ant = 0;
}

void loop() {
  if (!encendido){          //VELA APAGADA: Sondeamos valores del NTC.
    int valor = analogRead(A0);
    
    if (valor < 350){
      if (!valor_ant){
        valor_ant = valor;
      } else if ((valor < 200) && (valor < valor_ant)) {    //Hemos comprobado que el valor del NTC cae y es menor que el anterior en 0.1 segundos.
        encendido = 1;
        digitalWrite(2, 1);
        delay(400);
      } else valor_ant = 0;   
    }

    delay(100);

  } else {                //VELA ENCENDIDA: Sondeamos valores del micro.
    if (analogRead(A1) > 500){
      int num_umbral = 0;

      for (int i = 0; i < 10; i++){       //MAL?
        delay(50);
        if (analogRead(A1) > 550) num_umbral++;
      }

      if (num_umbral >= 5){               //En 0.5s comprobamos si sobrepasamos el umbral al menos 5 veces.
        encendido = 0;
        digitalWrite(2, 0);
        delay(200);
      }
    }
  }

  delay(50);
}
