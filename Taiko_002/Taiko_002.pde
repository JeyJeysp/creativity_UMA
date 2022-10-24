PImage fondo,taiko_rojo,taiko_azul;
import processing.serial.*;
ArrayList<Taiko> taikos;
ArrayList<Score> scores;
Serial myPort;
float position;
int score=0;
int acertado;

void setup()
{
  size(displayWidth,displayHeight);
  background(255,255,255);
  taikos = new ArrayList<Taiko>();
  scores = new ArrayList<Score>();
  printArray(Serial.list());
  myPort = new Serial(this, Serial.list()[0], 9600);
  myPort.bufferUntil(10);
  myPort.clear();
  fondo = loadImage("fondo.jpg");
  taiko_rojo = loadImage("taiko_rojo.png");
  taiko_azul = loadImage("taiko_azul.png");
  
}

void draw()
{
  if(random(100.0)>99.0)
  {
      creaTaiko();
  }
  //background(155, 226, 244);
  image(fondo,0,0,displayWidth,displayHeight);
  fill(color(255,255,255));
  textSize(63);
  text(score,195,335);
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
      score-=1;
      creaScore(-1);
      
    }
  }
  
  for (int i = 0; i<scores.size(); i++)
  {
    Score s = scores.get(i);
    s.update();
    s.draw();
  }
}
void mousePressed()
{
 //creaTaiko(); 
 acertado=0;
 for (int i = 0; i<taikos.size(); i++)
      {
        Taiko g = taikos.get(i);
        position=g.position();
        if (position>250 && position<400)
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
        }
}

void serialEvent(Serial p)
{
  String datoS = p.readString();
  datoS = datoS.trim();
  //println(datoS);
  if (datoS.equals("Knock!"))
  {
      acertado=0;
      for (int i = 0; i<taikos.size(); i++)
      {
        Taiko g = taikos.get(i);
        position=g.position();
        if (position>575 && position<720)
        {
            score+=1;
            creaScore(1);
            acertado=1;
        }       
      }
        if(acertado==0)
        {
          score-=1;
          creaScore(-1);
        }
          
  }
  }

void creaTaiko()
{
  if(random(2.0)>=1.0)
  {
    taikos.add(new Taiko(taiko_rojo,taikos));
    println(taikos.size());
  }
  else
  {
    
    taikos.add(new Taiko(taiko_azul, taikos));
    println(taikos.size());
  }
}
void creaScore(int x)
{
 scores.add(new Score(color(0,0,255),x));
    println(scores.size()); 
}
