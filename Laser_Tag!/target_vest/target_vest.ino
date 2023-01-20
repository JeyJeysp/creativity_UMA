//--------------------------------------------------//
// TITLE: Target Vest code                          //
// AUTHORS: A Pena Castillo, JJ Navarrete Galvez    //
//--------------------------------------------------//



// --- INCLUDES --- //
#include <Adafruit_NeoPixel.h>



// --- DEFINITIONS --- //
// - Time - //
#define MIN_DELAY 5
#define MAX_DELAY 25

// - Pin - //
#define LDR_B A0    //Back
#define LDR_RS A1    //Right Shoulder
#define LDR_LS A2   //Left Shoulder
#define LDR_C A3    //Chest
#define PIN_STRIP 12
#define PIN_SPEAKER 13

// - Otros - //
#define THRESHOLD 475
#define MAX_HEALTH 6
#define NUM_LED 13
#define MIN_brightness 10
#define MAX_brightness 100
#define RESET -1
#define GAME 0
#define HURTx1 1
#define HURTx2 2
#define GAME_OVER 3



// --- GLOBLAL VARIABLES --- //
// - General - //
uint8_t mode;
int health;

// - Sounds - //
int sound_1H[8] = {400, 500, 400, 500, 400, 500, 400, 500};
int sound_SS[10] = {400, 450, 550, 500, 400, 500, 450, 350, 450, 400};

// - Neopixel - //
int ipx;
int brightness;
int pulse_increase;
int brightness_increase;
int pulse_wait;
bool up;
unsigned long TIME_neopx;
Adafruit_NeoPixel strip(NUM_LED, PIN_STRIP, NEO_GRB + NEO_KHZ800);



// --- FUNCTION DEFINITIONS --- //
void speaker_sound(int id);
void lights(int id);



// --- Setup & Loop --- //
//*****************************************************************************
//
//! void setup()
//!
//! Initial configuration function. It initializes all variables and
//! configures the neopixels strip.
//
//*****************************************************************************
void setup() {
  Serial.begin(9600);
  pinMode(PIN_SPEAKER, OUTPUT);

  mode = GAME;
  health = MAX_HEALTH;
  
  brightness = MAX_brightness;
  pulse_wait = MAX_DELAY;
  pulse_increase = 1 + ((MAX_DELAY - MIN_DELAY) / health);
  brightness_increase = 1 + ((MAX_brightness - MIN_brightness) / health);
  TIME_neopx = 0;
  up = false;
  strip.begin();
  strip.show();
}


//*****************************************************************************
//
//! void loop()
//!
//! Most important loop in this code. It will check all the LDR and will manage
//! the health count. At the same time it will call 'speaker_sound' and 'lights'
//! functions when needed.
//
//*****************************************************************************
void loop() {
  lights(GAME);

  int i;
  int hurt = -1;
  int minimum = THRESHOLD;
  int readings[4];
    readings[0] = analogRead(LDR_B);
    readings[1] = analogRead(LDR_RS);
    readings[2] = analogRead(LDR_LS);
    readings[3] = analogRead(LDR_C);
    
  for (i=0; i<4; i++){
    if (readings[i] < minimum){
      minimum = readings[i];
      hurt = i;
    }
  }


  //IMPACT MANAGEMENT
  if (hurt >= 0) {     
      ipx = 0;  
    
    if ((hurt == 1) || (hurt == 2)){
      health--;
      
      if (health <= 0){
        speaker_sound(GAME_OVER);
        
        pulse_wait = MAX_DELAY;
        brightness = MAX_brightness;
        up = false;
      } else {
        speaker_sound(HURTx1);
        pulse_wait -= pulse_increase;
      }
    }
    
    else if ((hurt == 0) || (hurt == 3)){
      health -= 2;

      if (health <= 0){
        speaker_sound(GAME_OVER);
        
        pulse_wait = MAX_DELAY;
        brightness = MAX_brightness;
        up = false;
      } else {
        speaker_sound(HURTx2);
        pulse_wait -= pulse_increase*2;
      }
    }
  }
}



// --- FUNCTIONS --- //
//*****************************************************************************
//
//! void speaker_sound(int id)
//!
//! This function will reproduce sound using the speaker and 'tone'. It will
//! also call the lights function when needed.
//
//*****************************************************************************
void speaker_sound (int id){
  int i;

  if (id == HURTx1){
    for (i=0; i<8; i++){
      lights(HURTx1);
      tone(PIN_SPEAKER, sound_1H[i]);

      delay(100);
    }

    noTone(PIN_SPEAKER);
  }
  
  else if (id == HURTx2) {
    for (i=0; i<10; i++){
      lights(HURTx2);
      tone(PIN_SPEAKER, sound_SS[i]);
  
      if ((i == 3) || (i == 6) || (i == 9)) delay(280);
      else delay(140);
  
      noTone(PIN_SPEAKER);
      delay(25);
    }
  }

  else if (id == GAME_OVER){
    int sound_GO;
    lights(RESET);
    
    for (sound_GO=400; sound_GO>100; sound_GO -= 10){
      tone(PIN_SPEAKER, sound_GO);
      delay(50);
    }

    for (health=0; health<MAX_HEALTH; health++){
      lights(GAME_OVER);
      tone(PIN_SPEAKER, sound_GO);
      delay(400);

      lights(GAME_OVER);
      noTone(PIN_SPEAKER);
      delay(400);
    }
  }
}


//*****************************************************************************
//
//! void lights (int id)
//!
//! This function will manage the neopixel strip.
//
//*****************************************************************************
void lights(int id){
  int i;
  unsigned long time_now = millis();
  
  if (id == RESET){                                  //TURN OFF STRIP
    strip.clear();
    strip.show();
  }
  
  else if (id == GAME){                              //Pulse
    if (time_now > TIME_neopx + pulse_wait){
      TIME_neopx += pulse_wait;
      strip.setBrightness(brightness);
      
      for (i=0; i<strip.numPixels(); i++)
        strip.setPixelColor(i, strip.Color(50, 0, 0));
      
      strip.show();
      TIME_neopx = time_now;
    
      if (up){
        brightness++;
        if (brightness >= MAX_brightness){
          brightness = MAX_brightness;
          up = false;
        }
      } else {
        brightness--;
        if (brightness <= MIN_brightness){
          brightness = MIN_brightness;
          up = true;
        }
      }
    }
  }

  else if (id == HURTx1){                              //Yellow blink
    strip.clear();
    
    for(i=ipx; i<strip.numPixels(); i+=2)
      strip.setPixelColor(i, strip.Color(250, 150, 0));

    strip.show();
    ipx++;

    if (ipx >= 2) ipx = 0;
  }

  else if (id == HURTx2){                              //Orange blink
    strip.clear();
    
    for(i=ipx; i<strip.numPixels(); i+=2)
      strip.setPixelColor(i, strip.Color(255, 50, 0));

    strip.show();
    ipx++;

    if (ipx >= 2) ipx = 0;
  }

  else if (id == GAME_OVER){                              //incremento intensidad
    if ((ipx % 2) == 0){ 
      if (ipx == 0) brightness = MIN_brightness;
      
      strip.setBrightness(brightness);
      
      for (i=0; i<strip.numPixels(); i++)
        strip.setPixelColor(i, strip.Color(50, 0, 0));
  
      strip.show();
      
      brightness += brightness_increase;
      ipx++;
    } else {      
      strip.clear();
      strip.show();

      ipx++;
    } 
  }
}
