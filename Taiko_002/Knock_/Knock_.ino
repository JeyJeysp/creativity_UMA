const int ledPin = 13;//LED conectado al pin 13
const int KnockSensor = A0;//El piezo está conectado al pin A0
const int threshold = 100;//Umbral

int sensorReading = 0;
int ledState = LOW;

void setup() {
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  sensorReading = analogRead(KnockSensor);

  //Serial.println(sensorReading);
  if(sensorReading >= threshold)
  {
    ledState != ledState;
    digitalWrite(ledPin, ledState);
    Serial.println("Knock!");
  }

  delay(100);
 
}
