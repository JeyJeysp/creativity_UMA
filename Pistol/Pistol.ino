    /* This example demonstrates use of the internal temperature sensor.
|  Be sure to read the datasheet, particularly the part about how
\  the sensor is basically uncalibrated. */
#define Ray 6 
#define Led 5
#define Trigger 4
#define buzzer 7
int pressed=0;
int time_out=0;
unsigned long time_pass1=0, time_pass2=0, antibounce = 0, timeled=0;
int ammunition=20;
int shoot=0;
int no_ammo=0;
int led_blink=0;
int led=0;
void setup(){

  pinMode(Ray,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(Led,OUTPUT);
  pinMode(Trigger,INPUT_PULLUP);
  Serial.begin(9600);
}

void loop()
{
  unsigned long time_=millis();
  Serial.print("ammunition: ");
  Serial.println(ammunition);
  //modo=digitalRead(P4);
  //if(modo == 0)
    if(digitalRead(Trigger) == 0 && shoot == 0 && time_ - antibounce > 200 && time_out == 0 && ammunition>0)
    {
      digitalWrite(Ray,HIGH);
      time_pass1=time_;
      shoot=1;
      ammunition--;
      time_out = 1;
      for(int x = 4000; x > 1000; x--)
      {
        tone(buzzer,x);
      };
      noTone(buzzer);
      if(ammunition == 0)
      {
        no_ammo = 1;
        time_pass2=time_;
        digitalWrite(Led,HIGH);
        led_blink = 1;
      }
    }else if(digitalRead(Trigger) == 1 && shoot == 1)
    {
      shoot = 0;

    }   else if(time_-time_pass1>50 && time_out == 1)
    {  
      digitalWrite(Ray,LOW);
      antibounce = time_;
      time_out = 0;
    }else if(time_-time_pass2>10000 && no_ammo == 1)
    {
      digitalWrite(Led,LOW);
      ammunition=20;
      time_out = 0;
      shoot = 0;
      no_ammo = 0;
      led_blink=0;
    } else if(led_blink == 1 && time_ - timeled > 500)
    {
      timeled = time_;
      if(led == 0)
      {
        digitalWrite(Led,0);
        led+=1;
      } else
      {
        digitalWrite(Led,1);
        led-=1;
      }
    }
  } 
