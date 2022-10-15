//--------------------------------------------------//
// EJERCICIO 1: La Lampara-Vela						//
// AUTORES: A Pena Castillo, JJ Navarrete Galvez	//
//--------------------------------------------------//


// --- Definiciones --- //
#define intervalo 200
#define un_segundo 1000
#define UMBRAL_NTC 350
#define UMBRAL_Micro 600


// --- Variables globales --- //
int encendido, valor_ant, num_umbral;
unsigned long tiempo_ant;


// --- Setup y Loop --- //
void setup() {
	Serial.begin(9600);
	pinMode(2, OUTPUT);

	encendido = 0;
	valor_ant = 0;
	tiempo_ant = 0;
	num_umbral = 0;
}

void loop() {
	if (!encendido){          //VELA APAGADA: Sondeamos valores del NTC.
		int valor = analogRead(A0);
		unsigned long tiempo = millis();
    //Serial.print("TEMP: ");
    //Serial.println(valor);
    
		if (valor < 490){
			if (!valor_ant){
				valor_ant = valor;
				tiempo_ant = tiempo;
			} else if ((valor < 475) && (valor < valor_ant) && (tiempo > (tiempo_ant + intervalo))) {    //Hemos comprobado que el valor del NTC cae y es menor que el anterior en 0.1 segundos.
				Serial.println("        ENCIENDO");
				encendido = 1;
				valor_ant = 0;
				tiempo_ant = 0;
		
				digitalWrite(2, 1);
			} else if (((valor < 200) && (valor > valor_ant)) || (tiempo > (tiempo_ant + un_segundo))){
				valor_ant = 0;
				tiempo_ant = 0;
			}
		}
	} else {                //VELA ENCENDIDA: Sondeamos valores del micro.
		int valor2 = analogRead(A1);
    //Serial.print("MICRO: ");
    Serial.println(valor2);
    int tiempo = millis();
		  
		if (valor2 > 700){
      if (!tiempo_ant){
        tiempo_ant = tiempo;
      } else if ((valor2 > 700) && (tiempo > (tiempo_ant + intervalo*2))) {    //Hemos comprobado que el valor del NTC cae y es menor que el anterior en 0.1 segundos.
        Serial.println("        APAGO");
        encendido = 0;
        tiempo_ant = 0;
    
        digitalWrite(2, 0);
      } else if (tiempo > (tiempo_ant + un_segundo*2)){
        tiempo_ant = 0;
      }
		
		/*int umbral = 650;
		if (valor2 > umbral){
			int i = 0;
			tiempo_ant = millis();
			
			while (i < 10){
				if (millis() > (tiempo_ant + intervalo*i)){
					i++;
          valor2 = analogRead(A1);
          //Serial.print("MICRO DD: ");
          Serial.println(valor2);
          
					if (valor2 > umbral)
         {
						num_umbral++;
           umbral-=50;
         }
				}
			}
			
			if (num_umbral > 2){               //Comprobamos si sobrepasamos el umbral al menos 6 veces.
				Serial.println("        APAGO");
				
				encendido = 0;
				num_umbral = 0;
				tiempo_ant = 0;
				
				digitalWrite(2, 0);
			} else {
				num_umbral = 0;
				tiempo_ant = 0;
			}*/
		}
	}
}
