//--------------------------------------------------//
// EJERCICIO 1: La Lampara-Vela	   					//
// AUTORES: A Pena Castillo, JJ Navarrete Galvez	//
//--------------------------------------------------//


// --- Definiciones --- //
#define intervalo 50
#define un_segundo 1000
#define PORCENTAJE 0.97
#define UMBRAL_Micro 650


// --- Variables globales --- //
int encendido, valor_ant, num_umbral, valor_cambio;
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
   		Serial.println(valor);		
		
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
	if((valor_cambio > v-10) && (valor_cambio != 0))
    	v = analogRead(A0);
	else {
    	valor_cambio = 0;
		
		if (!valor_ant){
			valor_ant = v;
			tiempo_ant = t;
		} else if ((v < (valor_ant * PORCENTAJE)) && (t > (tiempo_ant + intervalo*2))){    //Hemos comprobado que el valor del NTC cae y es menor que el anterior en 0.1 segundos.
			//Serial.println("        ENCIENDO");
			encendido = 1;
			valor_ant = 0;
			tiempo_ant = 0;
     	valor_cambio = 0;
		
			digitalWrite(2, 1);
		} else if ((v > valor_ant) || (t > (tiempo_ant + un_segundo/4))){
			valor_ant = 0;
			tiempo_ant = 0;
		}
	}
}


void comprobarMicro (int v, unsigned long t){
	if (v > UMBRAL_Micro){
		if (!tiempo_ant)
			tiempo_ant = t;
		else if ((v > UMBRAL_Micro) && (t > (tiempo_ant + intervalo*4))){
			if(num_umbral < 3)
				num_umbral++;
			else{
				//Serial.println("        APAGO");
				valor_cambio = analogRead(A0);
				//Serial.print("Valor en el cambio:");
				//Serial.println(valor_cambio);
				
				encendido = 0;				
				tiempo_ant = 0;
				num_umbral = 0;

				digitalWrite(2, 0);        
		  	}
		} else if (t > (tiempo_ant + un_segundo/2)){
		  tiempo_ant = 0;
		  num_umbral = 0;
    	}
  	}
}
