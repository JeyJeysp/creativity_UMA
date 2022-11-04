import processing.sound.*;

SoundFile file,file1,file2,file3;
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
int intro=0;
int tiempo_trans=0;
float ale=99.0;
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
  file1 = new SoundFile(this,"Torero.wav");
  file2 = new SoundFile(this,"Sea_Shanty.wav");
  file3 = new SoundFile(this,"Nokia.wav");// Cambiar nombre del archivo para cambiar la canción
  //file.loop();
  //file.play();
  //noCursor();
  //peppo=peppo_serio;
}

void draw()
{
  if(intro == 0)
  {
      background(155, 226, 244);
      fill(color(0,0,0));
      textFont(fuente);
      textSize(63);
      text("Torero",800,350);
      text("Sea Shanty",800,500);
      text("Nokia ringtone",800,700);
  }
  else
  {  
    if((millis()-tiempo_trans)/1000 > file.duration()-1)
    {
      exit(); 
    }
    if(random(100.0)>ale)
    {
      creaTaiko();
    }
    image(fondo,0,0,displayWidth,displayHeight);
    image(peppo,40,displayHeight/2-192,180,180);
    fill(color(255,255,255));
    textFont(fuente);
    textSize(63);
    text(score,170,335);
    fill(color(232,204,215));
    for (int i = 0; i<taikos.size(); i++)
    {   
      Taiko g = taikos.get(i);
      g.update();
      g.draw();
      if(g.position()<200)
      {
        g.suicide();
        peppo=peppo_triste;
        if(score>0)
        {
          score-=1;
        }
        creaScore(-1); 
        if(((score+1) % 10 == 0))
        {
          if(l>-5)
          {
            l-=5;
          }
          creaLevel(1);
          ale+=0.1;
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
}
void mousePressed()
{
  if(intro==0)
  {
    if(mouseX > 800 && mouseX < 1000 && mouseY > 300 && mouseY < 400)
    {
      file1.play();
      file=file1;
      tiempo_trans=millis();
      intro=1;
      noCursor();
    } else if(mouseX > 800 && mouseX < 1000 && mouseY > 450 && mouseY < 550)
    {
      file2.play();
      file=file2;
      tiempo_trans=millis();
      intro=1;
      noCursor();
    } else if(mouseX > 800 && mouseX < 1000 && mouseY > 650 && mouseY < 750)
    {
      file3.play();
      file=file1;
      tiempo_trans=millis();
      intro=1;
      noCursor();
      
    }
  } 
  if(intro==1 && millis()-tiempo_trans>100)
  {
    accion();
  }
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
        ale-=0.1;
        }
      }       
   }
   if(acertado==0)
   {
     if(score>0)
     {
       score-=1;
     }
     creaScore(-1);
     peppo=peppo_triste;
     if(((score+1) % 10 == 0))
     {
       if(l>5)
       {
         l-=5;
       }
       creaLevel(1);
       ale+=0.1;
     }
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
