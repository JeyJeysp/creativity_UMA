//--------------------------------------------------//
// EJERCICIO 1: La Lampara-Vela						//
// AUTORES: A Pena Castillo, JJ Navarrete Galvez	//
//--------------------------------------------------//


// --- Definiciones --- //
#define intervalo 50
#define un_segundo 1000
#define UMBRAL_NTC 350
#define UMBRAL_Micro1 600
#define UMBRAL_Micro2 400


// --- Variables globales --- //
int encendido, valor_ant, num_umbral;
unsigned long tiempo_ant;


// --- Funciones --- //
void comprobarNTC (int v, unsigned long t);		//Funcion que chequea los valores del NTC y activa el rele.
void comprobarMicro (int v, unsigned long t);	//Funcion que chequea los valores del micro y desactiva el rele.


// --- Setup y Loop --- //
void setup() {
	Serial.begin(9600);
	pinMode(2, OUTPUT);		//El pin 2 se utilizara digitalmente para abrir/cerrar el rele.

	encendido = 0;			//Variable de control utilizada para gestionar el rele.
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
		
		comprobarNTC(valor, tiempo);
	} else {                //VELA ENCENDIDA: Sondeamos valores del micro.
		int valor2 = analogRead(A1);
		unsigned long tiempo2 = millis();
    	//Serial.print("MICRO: ");
    	//Serial.println(valor2);

		comprobarMicro(valor2, tiempo2);
	}
}



void comprobarNTC (int v, unsigned long t){
	if (valor < UMBRAL_NTC){
		if (!valor_ant){
			valor_ant = v;
			tiempo_ant = t;
		} else if ((valor < UMBRAL_NTC) && (valor < valor_ant) && (tiempo > (tiempo_ant + intervalo))){    //Hemos comprobado que el valor del NTC cae y es menor que el anterior en 0.1 segundos.
			//Serial.println("        ENCIENDO");
			encendido = 1;
			valor_ant = 0;
			tiempo_ant = 0;
		
			digitalWrite(2, 1);
		} else if (((valor < UMBRAL_NTC) && (valor > valor_ant)) || (tiempo > (tiempo_ant + un_segundo))){
			valor_ant = 0;
			tiempo_ant = 0;
		}
	}
}


void comprobarMicro (int v, unsigned long t){
	if ((v > UMBRAL_Micro1) || (v < UMBRAL_Micro2)){
		if (!tiempo_ant){
			tiempo_ant = t;
		} else if (((v > UMBRAL_Micro1) || (v < UMBRAL_Micro2)) && (t > (tiempo_ant + intervalo))){
			//Serial.println("        APAGO");
			encendido = 0;
			tiempo_ant = 0;

			digitalWrite(2, 0);
		} else if (t > (tiempo_ant + un_segundo)){
			tiempo_ant = 0;
		}
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
		}
	}*/
}
