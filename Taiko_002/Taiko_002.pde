import processing.sound.*;

SoundFile file;
PImage fondo,taiko_rojo,taiko_azul,peppo_feliz,peppo_triste,peppo_serio,peppo;
PFont fuente;
import processing.serial.*;
ArrayList<Taiko> taikos;
ArrayList<Score> scores;
ArrayList<Level> levels;
Serial myPort;
float position;
int score=0;
int acertado;
float x=0;
int level=0;
int l=10,cont=0;

void setup()
{
  size(displayWidth,displayHeight);
  background(255,255,255);
  taikos = new ArrayList<Taiko>();
  scores = new ArrayList<Score>();
  levels = new ArrayList<Level>();
  printArray(Serial.list());
  myPort = new Serial(this, Serial.list()[0], 9600);
  myPort.bufferUntil(10);
  myPort.clear();
  fondo = loadImage("fondo2.jpg");
  taiko_rojo = loadImage("taiko_rojo.png");
  taiko_azul = loadImage("taiko_azul.png");
  peppo_triste = loadImage("pepe_triste.jpg");
  peppo_feliz = loadImage("pepe_feliz.jpg");
  peppo_serio = loadImage("pepe_serio.jpg");
  peppo=peppo_feliz;
  fuente = createFont("Japonesa.ttf", 128);
  file = new SoundFile(this,"Sea_Shanty.wav");
  //file.loop();
  file.play();
  noCursor();
  //peppo=peppo_serio;
}

void draw()
{
  if(millis()/1000 > file.duration()-1)
  {
    exit(); 
  }
  if(random(100.0)>99.0)
  {
      creaTaiko();
  }
  //background(155, 226, 244);
  /*if(cont==(int)random(15.0,30.0))
  {
    cont=0;
    peppo=peppo_serio;
  }
  cont++;*/
  image(fondo,0,0,displayWidth,displayHeight);
  image(peppo,40,displayHeight/2-192,180,180);
  fill(color(255,255,255));
  textFont(fuente);
  textSize(63);
  text(score,170,335);
  fill(color(232,204,215));
  //ellipse(610,displayHeight/2-150,175,175);
  

  for (int i = 0; i<taikos.size(); i++)
  { 
    Taiko g = taikos.get(i);
    g.update();
    g.draw();
    if(g.position()<200)
    {
      g.suicide();
      peppo=peppo_triste;
      score-=1;
      creaScore(-1); 
      if(((score+1) % 10 == 0))
      {
        if(l>-5)
        {
          l-=5;
        }
        creaLevel(1);
      }
    }
  }
  for (int i = 0; i<scores.size(); i++)
  {
    Score s = scores.get(i);
    s.update();
    s.draw();
  }
  for (int i = 0; i<levels.size(); i++)
  {
    Level d = levels.get(i);
    d.update();
    d.draw();
  }
}
void mousePressed()
{
  accion();
 //creaTaiko(); 
 /*acertado=0;
 for (int i = 0; i<taikos.size(); i++)
 {
   Taiko g = taikos.get(i);
   position=g.position();
   if (position>300 && position<400)
   {
     score+=1;
     creaScore(1);
     acertado=1;
     g.suicide();
   }       
 }
 if(acertado==0)
 {
   score-=1;
   creaScore(-1);
 }*/
}

void serialEvent(Serial p)
{
  String datoS = p.readString();
  datoS = datoS.trim();
  //println(datoS);
  if (datoS.equals("Knock!"))
  {
    accion();
  }
 }
void accion()
{
  acertado=0;
  for (int i = 0; i<taikos.size(); i++)
  {
    Taiko g = taikos.get(i);
    position=g.position();
    if (position>250 && position<450)
    {
      score+=1;
      peppo=peppo_feliz;
      creaScore(1);
      acertado=1;
      g.suicide();
      if((score % 10 == 0))
      {
        l+=5;;
        creaLevel(0);
        }
      }       
   }
   if(acertado==0)
   {
     score-=1;
     creaScore(-1);
     peppo=peppo_triste;
     if(((score+1) % 10 == 0))
     {
       if(l>-5)
       {
         l-=5;
       }
       creaLevel(1);
     }
          /*if((score % 10 == 0))
          {
            creaLevel(1);
            for (int i = 0; i<taikos.size(); i++)
            {
                Taiko g = taikos.get(i);
                g.leveldown();
            }
          }*/
        }
}
void creaTaiko()
{
  if(random(2.0)>=1.0)
  {
    taikos.add(new Taiko(taiko_rojo,taikos,l));
    println(taikos.size());
  }
  else
  {
    
    taikos.add(new Taiko(taiko_azul, taikos,l));
    println(taikos.size());
  }
}
void creaScore(int x)
{
 scores.add(new Score(color(0,0,255),x,fuente));
    println(scores.size()); 
}
void creaLevel(int x)
{
 levels.add(new Level(x,fuente));
    println(levels.size()); 
}
