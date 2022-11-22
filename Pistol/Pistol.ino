/* This example demonstrates use of the internal temperature sensor.
|  Be sure to read the datasheet, particularly the part about how
\  the sensor is basically uncalibrated. */
  int pressed=0;
  int timeout=0;
  unsigned long timepass1=0, timepass2=0;
  int municion=50;
void setup(){

  pinMode(6,OUTPUT);
  pinMode(7,INPUT_PULLUP);
  Serial.begin(9600);
}
/*void loop()
{
  if(digitalRead(7) == 1)
  {
    digitalWrite(6,HIGH);
  } else {
    digitalWrite(6,LOW);
  }
}*/
void loop() {
  unsigned long tiempo=millis();
  Serial.print("Timepass1,timepass2: ");
  Serial.print(timepass1);
  Serial.print(" ");   
  Serial.println(timepass2);
  if(timeout == 1 && tiempo-timepass2>5000)
  {
    timeout=0;
  } else if(timeout==0)
  {
    if(digitalRead(7) == 0 && pressed == 0)
    {
      pressed=1;
      
      timepass1=tiempo;
      
      digitalWrite(6,HIGH);
    }
    else if(pressed == 1)
    {
      
      if(digitalRead(7) == 1)
      {
        digitalWrite(6,LOW);
        pressed=0;
      }
       else if(tiempo-timepass1>2000)
      {
        timeout=1;
        digitalWrite(6,LOW);
        timepass2=tiempo;
        pressed=0;
      }
    }
  }
  delay(50);
}
