  /* This example demonstrates use of the internal temperature sensor.
|  Be sure to read the datasheet, particularly the part about how
\  the sensor is basically uncalibrated. */
#define P1 2 
#define P2 3
#define P3 4
#define P4 5
  int pressed=0;
  int timeout=0;
  unsigned long timepass1=0, timepass2=0, antirrebotes = 0;
  int ammunition=10;
  int shoot=0;
  int no_ammo=0;
  int modo=-1;
  
void setup(){

  pinMode(P1,OUTPUT);
  pinMode(P2,OUTPUT);
  pinMode(P3,INPUT_PULLUP);
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
  /*modo=digitalRead(P4);
  if(modo == 1)
  {*/
    if(digitalRead(P3) == 0 && shoot == 0 && tiempo - antirrebotes > 200 && timeout == 0 && ammunition>0)
    {
      digitalWrite(P1,HIGH);
      timepass1=tiempo;
      shoot=1;
      ammunition--;
      timeout = 1;
      if(ammunition == 0)
      {
        no_ammo = 1;
        timepass2=tiempo;
        digitalWrite(P2,HIGH);
      }
    }else if(digitalRead(P3) == 1 && shoot == 1)
    {
      shoot = 0;

    }   else if(tiempo-timepass1>50 && timeout == 1)
    {  
      digitalWrite(P1,LOW);
      antirrebotes = tiempo;
      timeout = 0;
    }else if(tiempo-timepass2>10000 && no_ammo == 1)
    {
      digitalWrite(P2,LOW);
      ammunition=10;
      timeout = 0;
      shoot = 0;
      no_ammo = 0;
    }
  } /*else 
  {
    
    if(digitalRead(P3) == 0 && shoot == 0 && tiempo-timepass1 > 100 && timeout == 0 && ammunition>0)
    {
      Serial.println("AUTO 1");
      digitalWrite(P1,HIGH);
      timepass1=tiempo;
      shoot=1;
      ammunition--;
      //timeout = 1;
      if(ammunition == 0)
      {
        no_ammo = 1;
        timepass2=tiempo;
        digitalWrite(P2,HIGH);
      }
    } else if(digitalRead(P3) == 0 && tiempo-timepass1 > 50 && shoot == 1 && timeout == 0 && ammunition>0)
    {
      Serial.println("AUTO 2");
      digitalWrite(P1,LOW);
      timepass1=tiempo;
      shoot=0;
      ammunition--;
      //timeout = 1;
      if(ammunition == 0)
      {
        no_ammo = 1;
        timepass2=tiempo;
        digitalWrite(P2,HIGH);
      }
    }
    else if(digitalRead(P3) == 1)
    {
      digitalWrite(P1,LOW);
    }
    else if(tiempo-timepass2>10000 && no_ammo == 1)
    {
      digitalWrite(P2,LOW);
      ammunition=10;
      timeout = 0;
      shoot = 0;
      no_ammo = 0;
    }
}
}*/
