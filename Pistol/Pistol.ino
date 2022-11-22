/* This example demonstrates use of the internal temperature sensor.
|  Be sure to read the datasheet, particularly the part about how
\  the sensor is basically uncalibrated. */
  int pressed=0;
  int timeout=0;
  unsigned long timepass1=0, timepass2=0;
  int ammunition=10 ;
  int shoot=0;
  int no_ammo=0;
void setup(){

  pinMode(6,OUTPUT);
  pinMode(5,OUTPUT);
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
/*void loop() {
  unsigned long tiempo=millis();
  Serial.print("Timepass1,timepass2: ");
  Serial.print(timepass1);
  Serial.print(" ");   
  Serial.println(timepass2);
  if(timeout==0)
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
  } else if(timeout == 1 && tiempo-timepass2>5000)
  {
    timeout=0;
  } 
  delay(50);
}*/
void loop()
{
  unsigned long tiempo=millis();
    Serial.print("ammunition: ");
    Serial.println(ammunition);
   if(digitalRead(7) == 0 && shoot == 0 && timeout == 0 && ammunition>0)
  {
    Serial.println("2");
    digitalWrite(6,HIGH);
    timepass1=tiempo;
    shoot=1;
    ammunition--;
    timeout = 1;
    if(ammunition == 0)
    {
      no_ammo = 1;
      timepass2=tiempo;
      digitalWrite(5,HIGH);
    }
  }else if(digitalRead(7) == 1 && shoot == 1)
  {
    Serial.println("3");
    shoot = 0;
  } else if(tiempo-timepass1>50 && timeout == 1)
  {
      
    Serial.println("1");
    digitalWrite(6,LOW);
    timeout = 0;
  }else if(tiempo-timepass2>10000 && no_ammo == 1)
  {
    digitalWrite(5,LOW);
    ammunition=10;
    timeout = 0;
    shoot = 0;
    no_ammo = 0;
  }
}
