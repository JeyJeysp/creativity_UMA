
import processing.serial.*;
ArrayList<Taiko> taikos;
Serial myPort;
float position;
int score=0;
int acertado;

void setup()
{
  size(displayWidth,displayHeight);
  background(255,255,255);
  taikos = new ArrayList<Taiko>();
  printArray(Serial.list());
  myPort = new Serial(this, Serial.list()[0], 9600);
  myPort.bufferUntil(10);
  myPort.clear();
  
}

void draw()
{
  if(random(100.0)>98.0)
  {
      creaTaiko();
  }
  background(155, 226, 244);
  fill(color(0.0,0.0,0.0));
  textSize(126);
  text(score,100,100);
  fill(color(232,204,215));
  ellipse(200,displayHeight/2,175,175);
  

  for (int i = 0; i<taikos.size(); i++)
  {
    Taiko g = taikos.get(i);
    g.update();
    g.draw();
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
        if (position>110 && position<285)
        {
            score+=1;
            acertado=1;
        }       
      }
        if(acertado==0)
        {
          score-=1;
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
        if (position>200 && position<400)
        {
            score+=1;
            acertado=1;
        }       
      }
        if(acertado==0)
        {
          score-=1;
        }
          
  }
  }

void creaTaiko()
{
  if(random(2.0)>=1.0)
  {
    taikos.add(new Taiko(color(0,0,255)));
    println(taikos.size());
  }
  else
  {
    
    taikos.add(new Taiko(color(255,0,0)));
    println(taikos.size());
  }
}
