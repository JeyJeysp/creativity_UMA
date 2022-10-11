#define intervalo_1 100
#define intervalo_2 50
#define un_segundo 1000

int encendido, valor_ant, num_umbral;
unsigned long tiempo_ant;

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
    
		if (valor < 350){
			if (!valor_ant){
				valor_ant = valor;
				tiempo_ant = tiempo;
			} else if ((valor < 200) && (valor < valor_ant) && (tiempo > (tiempo_ant + intervalo_1))) {    //Hemos comprobado que el valor del NTC cae y es menor que el anterior en 0.1 segundos.
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
		if (analogRead(A1) > 600){
			int i = 0;
			tiempo_ant = millis();
			
			while (i < 10){
				if (millis() > (tiempo_ant + intervalo_2*i)){
					i++;
					
					if (analogRead(A1) > 600)
						num_umbral++;
				}
			}
			
			if (num_umbral > 6){               //Comprobamos si sobrepasamos el umbral al menos 6 veces.
				encendido = 0;
				num_umbral = 0;
				tiempo_ant = 0;
				
				digitalWrite(2, 0);
			} else {
				num_umbral = 0;
				tiempo_ant = 0;
			}
		}
	}
}
